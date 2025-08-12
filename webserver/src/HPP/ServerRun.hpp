#ifndef SERVER_RUN_HPP
#define SERVER_RUN_HPP

#include "../../inc/webserv.h"
#include "../../parse/config_parser.hpp"
#include "CGIExecutor.hpp"

class Client;

class ServerRun
{
  public:
	~ServerRun();

	void                      start();
	bool                      initializeServer(Server& server);
	int                       initServerSocket(int port, const std::string& addr);
	void                      epollLoop();
	void                      handleNewConnection(int client_fd);
	void                      handleNewEvent(int i, int client_fd);
	void                      handleCgiEvent(int i, int fd);
	void                      cleanUpClient(int fd);
	void                      enableEpollOut(int fd);
	void                      disableEpollOut(int fd);
	void                      checkTimeouts();
	static void               addFdToEpoll(int fd, uint32_t events);
	static void               registerCgiFds(int stdin_fd, int stdout_fd, int client_fd);
	static void               removeCgiFd(int fd);
	void                      handleCgiOutput(int cgi_fd, Client* client);
	void                      handleCgiInput(int cgi_fd, Client* client);
	bool                      cheak_cgi_status(Client* client, int fd);
	void                      cleanUpCgiProcess(int cgi_fd);
	static ServerRun&         getInstance();
	static void               destroyInstance();
	int&                      getEpollFd();
	int&                      getPort();
	struct epoll_event&       getEvent();
	const struct epoll_event& getEvents();
	std::map<int, Client*>&   getClients();
	Client*                   getClient(int fd);
	void                      setServers(const std::vector<Server>& servs);
	std::vector<Server>&      getServers();
	std::map<int, Server>     getServersFds();
	Server*                   getServerByHost(const std::string& host_header, int port);
	static void               stopServer();

  private:
	ServerRun();
	ServerRun(std::vector<Server> servs);

	static ServerRun*             _instance;

	static int                    _port;
	static std::map<int, Server>  _servers_fds;
	static int                    _epoll_fd;
	static struct epoll_event     _event;
	static struct epoll_event     _events[MAX_EVENTS];
	static std::map<int, Client*> _clients;
	static std::vector<Server>    _servers;

	static std::map<int, int>     _cgi_fd_to_client;

	static bool                   _is_running;
};

#include "Client.hpp"
#endif