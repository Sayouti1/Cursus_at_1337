#ifndef WEBSERV
#define WEBSERV

#include <algorithm>
#include <arpa/inet.h>
#include <csignal>
#include <cstring>
#include <ctime>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <set>
#include <sstream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

#define MAX_EVENTS      1024
#define TIMEOUT_SECONDS 60
#define TIMEOUT_CGI     10
#define EPOLL_TIMEOUT   1000

enum HttpMethod
{
	GET = 0,
	POST,
	DELETE,
	UNKNOWN = -1
};

namespace utils
{
	template <typename T>
	std::string toString(T value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	int          setToNonBlocking(int fd);
	std::string  getMIME(std::string ext);
	std::string  getFileExtension(std::string path);
	std::string  getHttpDate();
	void         printMessage(std::string msg, std::string col);
	void         displayProgressBar(size_t sent, size_t total);
	std::string  trim(const std::string& str);
	std::string  methodName(int n);
	std::string& toLowerString(std::string& str);
	std::string  toLowerString1(std::string str);
	std::string  toUpperCase(std::string str);

	bool         is_regular_file(const std::string& path);
	bool         isEquals(const std::string& a, const std::string& b);
	std::map<std::string, std::string>::const_iterator
	            findHeaderCaseInsensitive(const std::map<std::string, std::string>& headers, const std::string& key);
	void        printMap(const std::map<std::string, std::string> map);
	std::string removeLocationFromPath(std::string location, std::string path);
	bool        isRequestLineValid(const std::string& request);
	std::string extractHostname(const std::string& host_header);
	void        sig_handler(int sig);
	void        setProperStatusCodeBody(int exit_code, int& s_code, std::string& body);
	std::string getExtFromMIME(std::string header);

}

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"

#endif