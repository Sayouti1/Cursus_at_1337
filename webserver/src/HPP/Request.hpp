#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../../inc/webserv.h"
#include "../../parse/config_parser.hpp"
#include "CGIExecutor.hpp"
#include "Response.hpp"

class ServerRun;
class Client;

class Request
{
  public:
	Request(Client* client);
	~Request();

	bool                                executeCgi();
	void                                splitScriptAndPathInfo(const std::string& path, std::string& script_name, std::string& path_info);
	std::string                         get_script_filename(const std::string& s_name);
	void                                clearRequest();
	std::string&                        getRequest();
	int                                 processRequest();
	int                                 parseRequest();
	bool                                parseRequestLine(std::string& method_str);
	bool                                parse_headers_from_request_string();
	int                                 parseBody();
	void                                cheak_loaction();
	int                                 saveBodyAsFile();
	int                                 getMethod();
	std::string&                        getPath();
	std::string&                        getProtocol();
	std::vector<char>&                  getBody();
	std::map<std::string, std::string>& getHeaders();
	bool                                isKeepALive();
	void                                setKeepAlive(bool is);
	bool                                isCgi();
	bool                                isChunked();
	bool                                hasHeader(std::string header);
	Response&                           getResponse();
	int                                 processGetRequest();
	int                                 processPostRequest();
	int                                 processDeleteRequest();
	int                                 parsePostBody();
	size_t                              bodyLengthReceived();
	size_t                              getContentLength();
	bool                                readChunkedBody();
	std::map<std::string, std::string>& getParameters();
	void                                setParameter(std::string key, std::string value);
	bool                                headersParsed();
	void                                setHeadersParsed(bool is);
	int                                 parseHeaders();
	int                                 handleHttpMethod();
	bool                                handleParsing();
	bool                                handleMethodValidation();
	int                                 handleCgi();
	int                                 handleRedirection();
	void                                setDefaultHeaders();
	std::string                         getPostFilename();
	Client*                             getClient();
	Location&                           getLocation();
	bool                                isAllowedMethod();
	int                                 generateAutoindex(const std::string& dir_path);
	CGIExecutor&                        getCGIExecutor();

  private:
	HttpMethod                         _method;

	std::string                        _path;
	std::string                        _host;
	int                                _host_port;
	std::string                        _query_string;
	std::string                        _protocol;
	std::map<std::string, std::string> _headers;
	std::vector<char>                  _body;
	bool                               _keep_alive;
	std::map<std::string, std::string> _parameters;
	bool                               _is_cgi;
	bool                               _parsedHeaders;
	size_t                             _content_length;
	std::string                        _content_type;
	bool                               _is_valid;
	std::string                        _parse_error;
	Response                           _response;
	std::string                        _request;

	CGIExecutor                        _cgi_executor;
	Location*                          _location;
	Server*                            _server;
	std::map<int, CGIExecutor*>*       _cgi_map;
	Client*                            _client;
};

#include "ServerRun.hpp"
#endif // REQUEST_HPP
