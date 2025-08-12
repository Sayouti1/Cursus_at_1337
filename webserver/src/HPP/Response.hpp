#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "../../inc/webserv.h"
#include "../../parse/config_parser.hpp"

class Response
{
  public:
	Response();

	~Response();

	Response&          setProtocol(std::string protocol);
	Response&          setStatusCode(int code);
	Response&          setHeader(std::string key, std::string value);
	Response&          setBody(std::vector<char> body);
	Response&          setBody(std::string body);
	void               setIsSendingHeaders(bool is);
	void               setIsSendingBody(bool is);
	void               setHeadersOffset(int offset);
	void               setBodyOffset(int offset);
	void               setAllDataSent(bool is);
	void               setDefaultBody();
	std::string        getProtocol();
	std::string&       getStatusMessage();
	int                getStatusCode();
	std::string        getHeader(std::string key);
	std::vector<char>& getBody();
	bool               isSendingHeaders();
	bool               isSendingBody();
	bool               isAllDataSent();
	bool               isResponseStarted();
	size_t             getBodyOffset();
	int                getHeadersOffset();
	void               clearResponse();
	std::string        gatherResponseHeaders();
	void               checkCustomErrorPage(Server* server);
	int                sendResponse(int fd);
	int                prepareBadRequest(Server* server);
	void               setDefaultHeaders();
	int                handleRedirection(std::pair<int, std::string> redirect);

  private:
	int                                _status_code;
	std::string                        _protocol;
	std::string                        _status_message;
	std::map<std::string, std::string> _headers;
	std::vector<char>                  _body;
	bool                               _is_sending_headers;
	bool                               _is_sending_body;
	size_t                             _body_offset;
	size_t                             _header_offset;
	bool                               _is_all_data_sent;
};

#endif