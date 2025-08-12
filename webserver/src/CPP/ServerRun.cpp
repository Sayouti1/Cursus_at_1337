#include "../HPP/ServerRun.hpp"
#include <unistd.h>

ServerRun*             ServerRun::_instance = NULL;
int                    ServerRun::_port     = 0;
std::map<int, Server>  ServerRun::_servers_fds;
int                    ServerRun::_epoll_fd = -1;
struct epoll_event     ServerRun::_event;
struct epoll_event     ServerRun::_events[MAX_EVENTS];
std::map<int, Client*> ServerRun::_clients;
std::vector<Server>    ServerRun::_servers;
std::map<int, int>     ServerRun::_cgi_fd_to_client;
bool                   ServerRun::_is_running = true;

void                   ServerRun::epollLoop()
{
	while (_is_running)
	{
		int num_events = epoll_wait(_epoll_fd, _events, MAX_EVENTS, EPOLL_TIMEOUT);
		if (num_events == -1)
			break;

		time_t now = time(NULL);

		for (int i = 0; i < num_events; i++)
		{
			int fd = _events[i].data.fd;

			if (_servers_fds.find(fd) != _servers_fds.end())
				handleNewConnection(fd);
			else if (_clients.find(fd) != _clients.end())
			{
				handleNewEvent(i, fd);
				if (_clients.find(fd) != _clients.end())
					_clients[fd]->setLastActivity(now);
			}
			else if (_cgi_fd_to_client.find(fd) != _cgi_fd_to_client.end())
				handleCgiEvent(i, fd);
		}
		checkTimeouts();
	}
}

void ServerRun::handleCgiEvent(int i, int fd)
{
	std::map<int, int>::iterator it = _cgi_fd_to_client.find(fd);
	if (it == _cgi_fd_to_client.end())
	{
		epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
		if (fd > 0)
			close(fd);
		return;
	}

	int                              client_fd = it->second;
	std::map<int, Client*>::iterator client    = _clients.find(client_fd);
	if (client == _clients.end())
	{
		cleanUpCgiProcess(fd);
		return;
	}

	if (_events[i].events & (EPOLLHUP | EPOLLERR))
	{
		cleanUpCgiProcess(fd);
		return;
	}

	if (_events[i].events & EPOLLIN)
		handleCgiOutput(fd, client->second);
	if (_events[i].events & EPOLLOUT)
		handleCgiInput(fd, client->second);
}

void ServerRun::handleCgiOutput(int cgi_fd, Client* client)
{
	client->getRequest().getCGIExecutor().getState();

	client->getRequest().getCGIExecutor().readCgiOutput(cgi_fd);
	int   status;
	int   cgi_pid = client->getRequest().getCGIExecutor().getCgiPid();
	pid_t result  = waitpid(cgi_pid, &status, WNOHANG);
	if (result == cgi_pid)
	{
		client->getRequest().getCGIExecutor().getCgiPid() = -1;
	}
	if (client->getRequest().getCGIExecutor().getState() == CGIExecutor::DONE)
	{
		client->getRequest().getCGIExecutor().parseCgiOutput(client->getRequest().getResponse());
		client->getRequest().getResponse().setStatusCode(200);
		enableEpollOut(client->getFd());
	}
}

void ServerRun::handleCgiInput(int cgi_fd, Client* client)
{
	client->getRequest().getCGIExecutor().writeToCgiInput(cgi_fd);
}

void ServerRun::cleanUpCgiProcess(int cgi_fd)
{
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, cgi_fd, NULL);
	if (cgi_fd > 0)
		close(cgi_fd);

	_cgi_fd_to_client.erase(cgi_fd);
}

void ServerRun::handleNewEvent(int i, int fd)
{
	if (_events[i].events & (EPOLLERR | EPOLLHUP))
		return cleanUpClient(fd);

	if (_events[i].events & EPOLLIN)
	{
		int ret = _clients[fd]->readRequest();
		if (ret < 0)
			return cleanUpClient(fd);

		if (ret == 2)
		{
			int status = _clients[fd]->getRequest().processRequest();
			if (status == -1 || !_clients[fd]->getRequest().isCgi())
				enableEpollOut(fd);
		}
	}

	if (_events[i].events & EPOLLOUT)
	{
		int ret = _clients[fd]->getRequest().getResponse().sendResponse(fd);
		if (ret == -1)
			cleanUpClient(fd);
		else if (ret == 0)
		{
			if (_clients[fd]->getRequest().getResponse().isAllDataSent())
				disableEpollOut(fd);

			if (!_clients[fd]->getRequest().isKeepALive())
				cleanUpClient(fd);
			else
				_clients[fd]->clean();
		}
	}
}

void ServerRun::handleNewConnection(int event_fd)
{
	struct sockaddr_in client_addr;
	socklen_t          addr_len  = sizeof client_addr;

	int                client_fd = accept(event_fd, (struct sockaddr*)&client_addr, &addr_len);

	if (client_fd == -1)
	{
		utils::printMessage("ERROR, accept returns -1", COLOR_RED);
		return;
	}
	utils::setToNonBlocking(client_fd);

	_clients[client_fd]      = new Client(client_fd, client_addr, event_fd, &_servers_fds[event_fd]);

	_event.data.fd      = client_fd;
	_event.events       = EPOLLIN;

	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, client_fd, &_event);

	utils::printMessage("New Client Connected : " + utils::toString(client_fd), COLOR_GREEN);
}

bool ServerRun::cheak_cgi_status(Client* client, int fd)
{
	Request& req = client->getRequest();
	if (!req.isCgi() || req.getCGIExecutor().getCgiPid() <= 0)
		return false;
	int         status = 0;
	int         s_code = 0;
	std::string body;
	pid_t       pid    = req.getCGIExecutor().getCgiPid();
	pid_t       result = waitpid(pid, &status, WNOHANG);

	time_t      now    = time(NULL);
	if (now - req.getCGIExecutor().get_time() > TIMEOUT_CGI)
	{
		if (pid > 0)
		{
			kill(pid, SIGTERM);
			if (status != 0)
			{
				char** env = req.getCGIExecutor().get_env();
				req.getCGIExecutor().set_null_env();
				for (int i = 0; env && env[i] != NULL; i++)
					free(env[i]);
				delete[] env;
			}
			req.getCGIExecutor().getCgiPid() = -1;
		}
		removeCgiFd(req.getCGIExecutor().getStdinFd());
		removeCgiFd(req.getCGIExecutor().getStdoutFd());
		req.getResponse()
		    .setProtocol("HTTP/1.1")
		    .setStatusCode(504)
		    .setHeader("Content-Type", "text/plain")
		    .setHeader("Connection", "close")
		    .checkCustomErrorPage(client->getServer());
		req.setKeepAlive(false);
		enableEpollOut(fd);
		return true;
	}
	if (result == pid)
	{
		if (WIFEXITED(status))
		{
			int exit_code = WEXITSTATUS(status);
			utils::setProperStatusCodeBody(exit_code, s_code, body);
		}
		else if (WIFSIGNALED(status))
		{
			WTERMSIG(status);
			s_code = 500;
			body   = "Internal Server Error.";
		}
		req.getCGIExecutor().getCgiPid() = -1;

		removeCgiFd(req.getCGIExecutor().getStdinFd());
		removeCgiFd(req.getCGIExecutor().getStdoutFd());
		req.getResponse()
		    .setProtocol("HTTP/1.1")
		    .setStatusCode(s_code)
		    .setHeader("Content-Type", "text/plain")
		    .setHeader("Connection", "close")
		    .setBody(body)
		    .checkCustomErrorPage(client->getServer());
		req.setKeepAlive(false);
		enableEpollOut(fd);
		return true; // CGI was handled
	}
	return false; // CGI still running or not a CGI request
}

void ServerRun::checkTimeouts()
{
	int    status = 0;
	time_t now    = time(NULL);
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end();)
	{
		Client*  client = it->second;
		int      fd     = it->first;
		Request& req    = client->getRequest();
		if (cheak_cgi_status(client, fd))
			continue;
		if (now - client->getLastActivity() > TIMEOUT_SECONDS)
		{
			utils::printMessage("Client timeout =:> " + utils::toString(fd), COLOR_RED);

			if (req.isCgi() && req.getCGIExecutor().getCgiPid() > 0)
			{
				pid_t pid = req.getCGIExecutor().getCgiPid();
				if (pid > 0)
				{
					kill(pid, SIGTERM);
					waitpid(pid, &status, WNOHANG);
					if (status != 0)
					{
						char** env = req.getCGIExecutor().get_env();
						req.getCGIExecutor().set_null_env();
						for (int i = 0; env && env[i] != NULL; i++)
							free(env[i]);
						delete[] env;
					}
					req.getCGIExecutor().getCgiPid() = -1;
				}
				removeCgiFd(req.getCGIExecutor().getStdinFd());
				removeCgiFd(req.getCGIExecutor().getStdoutFd());
			}

			if (!req.getResponse().isResponseStarted())
			{
				req.getResponse()
				    .setProtocol("HTTP/1.1")
				    .setStatusCode(408)
				    .setHeader("Content-Type", "text/plain")
				    .setHeader("Connection", "close")
				    .checkCustomErrorPage(client->getServer());
				req.setKeepAlive(false);
				enableEpollOut(fd);
			}
			else
				cleanUpClient(fd);
		}
		++it;
	}
}

void ServerRun::enableEpollOut(int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events  = EPOLLIN | EPOLLOUT;

	if (epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &event) == -1)
		perror("epoll_ctl MOD failed");
}

void ServerRun::disableEpollOut(int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events  = EPOLLIN;

	if (epoll_ctl(_epoll_fd, EPOLL_CTL_MOD, fd, &event) == -1)
		perror("epoll_ctl MOD (disable EPOLLOUT) failed");
}

int ServerRun::initServerSocket(int port, const std::string& addr)
{

	int socket_fd = 0;
	socket_fd     = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		utils::printMessage("######### Error creating socket: ", COLOR_RED);
		return -1;
	}
	utils::setToNonBlocking(socket_fd);

	int opt = 1;
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		utils::printMessage("############## Error setting socket options: ", COLOR_RED);
		if (socket_fd > 0)
			close(socket_fd);
		return -1;
	}

	struct sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port   = htons(port);

	if (inet_pton(AF_INET, addr.c_str(), &server_addr.sin_addr) <= 0)
	{
		utils::printMessage("Invalid IP address: " + addr, COLOR_RED);
		close(socket_fd);
		return -1;
	}

	if ((bind(socket_fd, (const sockaddr*)&server_addr, sizeof server_addr)) == -1)
	{
		utils::printMessage("############# Error binding socket: ", COLOR_RED);
		if (socket_fd > 0)
			close(socket_fd);
		return -1;
	}
	if (listen(socket_fd, SOMAXCONN) == -1)
	{
		utils::printMessage("################## Error listening on socket: ", COLOR_RED);
		if (socket_fd > 0)
			close(socket_fd);
		return -1;
	}
	return socket_fd;
}

bool ServerRun::initializeServer(Server& server)
{
	_port = server.get_listen();
	utils::printMessage("trying " + server.get_hoste() + " : " + utils::toString(server.get_listen()), COLOR_CYAN);
	int socket_fd = initServerSocket(_port, server.get_hoste());
	if (socket_fd < 0)
		return false;
	_event.events  = EPOLLIN;
	_event.data.fd = socket_fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, socket_fd, &_event) == -1)
	{
		utils::printMessage("#############3 Error adding server socket to epoll: ", COLOR_RED);
		if (socket_fd > 0)
			close(socket_fd);
		if (_epoll_fd > 0)
			close(_epoll_fd);
		return false;
	}
	_servers_fds.insert(std::pair<int, Server>(socket_fd, server));
	utils::printMessage("Server started on Port : " + utils::toString(_port), COLOR_MAGENTA);
	return true;
}

ServerRun::ServerRun()
{
	_instance      = NULL;
	_port          = 0;
	_epoll_fd      = -1;
	_event.events  = 0;
	_event.data.fd = -1;
	memset(&_event, 0, sizeof(_event));
	memset(_events, 0, sizeof(_events));
}

ServerRun::ServerRun(std::vector<Server> servs)
{
	_instance      = NULL;
	_port          = 0;
	_epoll_fd      = -1;
	_event.events  = 0;
	_event.data.fd = -1;
	setServers(servs);
}

ServerRun::~ServerRun() { }

ServerRun& ServerRun::getInstance()
{
	if (_instance == NULL)
		_instance = new ServerRun();
	return *_instance;
}

void ServerRun::start()
{
	_epoll_fd = epoll_create(1);
	if (_epoll_fd == -1)
	{
		utils::printMessage("############## Error creating epoll instance: ", COLOR_RED);
		return;
	}
	std::set<std::string> used_ports;
	for (size_t i = 0; i < _servers.size(); i++)
	{
		std::string port = _servers[i].get_hoste() + ":" + utils::toString(_servers[i].get_listen());

		if (used_ports.count(port))
		{
			utils::printMessage("IP:Port " + port + " already bound. Skipping.", COLOR_YELLOW);
			continue;
		}

		if (!initializeServer(_servers[i]))
			return;
		used_ports.insert(port);
	}
	signal(SIGINT, utils::sig_handler);
	signal(SIGQUIT, SIG_IGN);
	epollLoop();
}

void ServerRun::stopServer()
{
	_is_running = false;
	utils::printMessage("\n[SHUTDOWN] Server is shutting down gracefully...", COLOR_GREEN);
};

void ServerRun::destroyInstance()
{
	utils::printMessage("\n[SHUTDOWN] Destroying Server instance ...", COLOR_GREEN);
	for (std::map<int, Server>::iterator it = _servers_fds.begin(); it != _servers_fds.end(); it++)
	{
		if (it->first > 0)
			if (it->first > 0)
				close(it->first);
	}
	for (std::map<int, int>::iterator it = _cgi_fd_to_client.begin(); it != _cgi_fd_to_client.end(); it++)
	{
		if (it->first > 0)
			close(it->first);
	}
	std::map<int, Client*>::iterator it = _clients.begin();
	for (; it != _clients.end(); it++)
	{
		if (it->first > 0)
			if (it->first > 0)
				close(it->first);
		delete it->second;
	}

	if (_epoll_fd > 0)
		if (_epoll_fd > 0)
			close(_epoll_fd);

	delete _instance;
	_instance = NULL;
};

int& ServerRun::getEpollFd()
{
	return _epoll_fd;
}

int& ServerRun::getPort()
{
	return _port;
}

struct epoll_event& ServerRun::getEvent()
{
	return _event;
}

const struct epoll_event& ServerRun::getEvents()
{
	return *_events;
}

std::map<int, Client*>& ServerRun::getClients()
{
	return _clients;
}

void ServerRun::setServers(const std::vector<Server>& servs)
{
	for (std::vector<Server>::const_iterator it = servs.begin(); it != servs.end(); it++)
		_servers.push_back(*it);
}

std::vector<Server>& ServerRun::getServers()
{
	return _servers;
}

std::map<int, Server> ServerRun::getServersFds()
{
	return _servers_fds;
}

Client* ServerRun::getClient(int fd)
{
	return _clients[fd];
}

void ServerRun::cleanUpClient(int fd)
{
	// utils::printMessage("Cleanup client : " + utils::toString(fd), COLOR_RED);
	std::map<int, Client*>::iterator it = _clients.find(fd);

	if (it == _clients.end())
		return;

	close(it->second->getFd());
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, it->second->getFd(), NULL);
	Request& req = it->second->getRequest();
	if (req.isCgi())
	{
		if (req.getCGIExecutor().getCgiPid() > 0)
		{
			kill(req.getCGIExecutor().getCgiPid(), SIGTERM);
			waitpid(req.getCGIExecutor().getCgiPid(), NULL, WNOHANG);
			req.getCGIExecutor().getCgiPid() = -1;
		}
		removeCgiFd(req.getCGIExecutor().getStdinFd());
		removeCgiFd(req.getCGIExecutor().getStdoutFd());
	}
	delete it->second;
	_clients.erase(it);
}

Server* ServerRun::getServerByHost(const std::string& host_header, int port)
{
	std::vector<Server>& servers     = ServerRun::getInstance().getServers();
	std::string          target_host = utils::extractHostname(host_header);
	for (size_t i = 0; i < servers.size(); i++)
	{
		if (servers[i].get_listen() != port)
			continue;

		const std::vector<std::string>& names = servers[i].get_server_names();

		for (size_t j = 0; j < names.size(); j++)
		{
			if (names[j] == target_host)
				return &(servers[i]);
		}
	}

	for (size_t i = 0; i < servers.size(); i++)
	{
		if (servers[i].get_listen() == port)
			return &(servers[i]);
	}

	if (!servers.empty())
		return &(servers[0]);

	std::cout << "SErver NOOOOT FOUNDD !!!!" << std::endl;
	return NULL;
}

void ServerRun::registerCgiFds(int stdin_fd, int stdout_fd, int client_fd)
{

	if (stdin_fd >= 0)
	{
		_cgi_fd_to_client[stdin_fd] = client_fd;
		addFdToEpoll(stdin_fd, EPOLLOUT);
	}
	if (stdout_fd >= 0)
	{
		_cgi_fd_to_client[stdout_fd] = client_fd;
		addFdToEpoll(stdout_fd, EPOLLIN);
	}
}

void ServerRun::addFdToEpoll(int fd, uint32_t events)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events  = events;

	epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event);
}

void ServerRun::removeCgiFd(int fd)
{
	if (fd < 0)
		return;
	close(fd);
	epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd, NULL);
	_cgi_fd_to_client.erase(fd);
}