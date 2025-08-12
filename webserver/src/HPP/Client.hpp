#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../../inc/webserv.h"
#include "Request.hpp"

class Server;

class Client
{
  public:
	Client(int fd, struct sockaddr_in addr, int server_fd, Server* server);

	~Client();

	int      readRequest();
	int      getFd();
	Request& getRequest();
	Server*  getServer();
	int      getServerFd();
	time_t   getLastActivity();
	void     setLastActivity(time_t now);
	void     clean();
	void     setServer(Server* server);

  private:
	int     _fd;
	time_t  _last_activity;
	Request _request;
	int     _server_fd;
	Server* _server;
	Client();
};

#endif