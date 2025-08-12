#include "../HPP/Client.hpp"

Client::Client(int fd, struct sockaddr_in addr, int server_fd, Server* server)
    : _fd(fd)
    , _last_activity(time(NULL))
    , _request(this)
    , _server_fd(server_fd)
    , _server(server)
{
	(void)addr;
	_request.clearRequest();
}

Client::Client()
    : _fd(-1)
    , _last_activity(time(NULL))
    , _request(NULL)
    , _server(NULL)
{
	_request.clearRequest();
}

void Client::setServer(Server* server)
{
	_server = server;
}

Client::~Client()
{
}

int Client::readRequest()
{
	char    buffer[4096];

	ssize_t byte_read = recv(getFd(), buffer, sizeof(buffer) - 1, 0);

	if (byte_read < 0)
		return (-1);

	if (byte_read == 0)
		return (-2);

	_request.getRequest().append(buffer, byte_read);

	if (!utils::isRequestLineValid(_request.getRequest()))
	{
		_request.getRequest().clear();
		return (1);
	}

	if (!_request.headersParsed())
	{
		if (_request.getRequest().find("\r\n\r\n") == std::string::npos)
			return (1);
		_request.parse_headers_from_request_string();
	}

	if (_request.isChunked())
	{
		if (_request.getRequest().find("\r\n0\r\n\r\n") == std::string::npos)
			return (1);

		if (!_request.readChunkedBody())
			return (-1);
	}
	else if (_request.hasHeader("Content-Length"))
	{
		if (_request.bodyLengthReceived() < _request.getContentLength())
			return (1);
	}
	return (2);
}

int Client::getFd()
{
	return _fd;
}

Request& Client::getRequest()
{
	return _request;
}

int Client::getServerFd()
{
	return _server_fd;
}

void Client::clean()
{
	_request.clearRequest();
	_request.getResponse().clearResponse();
	_request.getCGIExecutor().clearCgi();
}

time_t Client::getLastActivity()
{
	return _last_activity;
}

void Client::setLastActivity(time_t now)
{
	_last_activity = now;
}

Server* Client::getServer()
{
	return _server;
}