#include "../HPP/Request.hpp"

Request::Request(Client* client)
    : _client(client)
{

	_method         = UNKNOWN;
	_keep_alive     = true;
	_is_cgi         = false;
	_parsedHeaders  = false;
	_content_length = 0;
	_is_valid       = true;

	clearRequest();
}

Request::~Request()
{
}

int Request::getMethod()
{
	return _method;
}

std::string& Request::getPath()
{
	return _path;
}

std::map<std::string, std::string>& Request::getHeaders()
{
	return _headers;
}

bool Request::isCgi()
{
	return _is_cgi;
}

bool Request::isChunked()
{
	std::map<std::string, std::string>::const_iterator it = utils::findHeaderCaseInsensitive(_headers, "Transfer-Encoding");
	return (it != _headers.end()) && (utils::toLowerString1(it->second) == "chunked");
}

bool Request::hasHeader(std::string header)
{
	return utils::findHeaderCaseInsensitive(_headers, header) != _headers.end();
}

Response& Request::getResponse()
{
	return _response;
}

size_t Request::bodyLengthReceived()
{
	std::size_t headers_end = _request.find("\r\n\r\n");
	if (headers_end == std::string::npos)
		return 0;
	std::size_t body_start = headers_end + 4;
	if (body_start >= _request.size())
		return 0;
	return (_request.size() - body_start);
}

bool Request::headersParsed()
{
	return _parsedHeaders;
}

size_t Request::getContentLength()
{
	return (_content_length);
}

void Request::setParameter(std::string key, std::string value)
{
	_parameters[key] = value;
}

void Request::setHeadersParsed(bool is)
{
	_parsedHeaders = is;
}

int Request::processRequest()
{
	_response.setDefaultHeaders();

	getClient()->setServer(ServerRun::getInstance().getServerByHost(_host, getClient()->getServer()->get_listen()));

	if (!handleParsing())
		return (-1);

	if (!handleMethodValidation())
		return -1;

	if (getLocation().get_is_redirect())
		return _response.handleRedirection(getLocation().get_return());
	if (isCgi())
		return handleCgi();

	return handleHttpMethod();
}

bool Request::handleParsing()
{
	int ret = parseRequest();
	if (ret == 200)
		return true;
	_response.setStatusCode(ret).checkCustomErrorPage(getClient()->getServer());
	return false;
}

bool Request::handleMethodValidation()
{
	if (isAllowedMethod())
		return true;

	std::string                     allowed_methods;
	const std::vector<std::string>& methods = getLocation().get_allow_methods();

	for (std::vector<std::string>::const_iterator it = methods.begin(); it != methods.end(); ++it)
	{
		allowed_methods += utils::toUpperCase(*it);
		if (it + 1 != methods.end())
			allowed_methods += ", ";
	}

	_response.setStatusCode(405)
	    .setHeader("Allow", allowed_methods)
	    .checkCustomErrorPage(getClient()->getServer());
	return false;
}

int Request::handleCgi()
{
	executeCgi();
	ServerRun::getInstance().registerCgiFds(_cgi_executor.getStdinFd(), _cgi_executor.getStdoutFd(), getClient()->getFd());
	return 0;
}

CGIExecutor& Request::getCGIExecutor()
{
	return _cgi_executor;
}

int Request::handleHttpMethod()
{
	int status = 0;

	if (getMethod() == GET)
		status = processGetRequest();
	else if (getMethod() == POST)
		status = processPostRequest();
	else if (getMethod() == DELETE)
		status = processDeleteRequest();
	else
	{
		_response.setStatusCode(405)
		    .setHeader("Allow", "GET, POST, DELETE")
		    .checkCustomErrorPage(getClient()->getServer());
		return -1;
	}

	_response.setStatusCode(status).checkCustomErrorPage(getClient()->getServer());

	return 0;
}

int Request::generateAutoindex(const std::string& dir_path)
{
	DIR* dir = opendir(dir_path.c_str());
	if (!dir)
	{
		_response.setStatusCode(403);
		return (403);
	}
	struct dirent*     entry;
	std::ostringstream html;
	html << "<html><body><h1>Index of " << dir_path << "</h1><ul>";

	while ((entry = readdir(dir)) != NULL)
		html << "<li><a href=\"" << entry->d_name << "\">" << entry->d_name << "</a></li>";

	html << "</ul></body></html>";

	closedir(dir);

	_response.setBody(html.str());
	return 200;
}

int Request::processGetRequest()
{
	std::string full_path = getLocation().get_root() + getPath();
	if (access(full_path.c_str(), F_OK) != 0)
		return 404;

	struct stat path_stat;

	if (stat(full_path.c_str(), &path_stat) != 0)
		return 500;

	if (S_ISDIR(path_stat.st_mode))
	{
		if (full_path[full_path.length() - 1] != '/')
			full_path += "/";

		std::string index_path = full_path + getLocation().get_index();
		if (access(index_path.c_str(), F_OK) == 0 && utils::is_regular_file(index_path))
			full_path = index_path;
		else
		{
			if (getLocation().get_autoindex())
			{
				if (generateAutoindex(full_path) != 200)
					return 403;
				_response.setHeader("Content-type", "text/html");
				return 200;
			}
			else
				return 403;
		}
	}

	if (access(full_path.c_str(), R_OK) != 0)
		return 403;

	std::ifstream file(full_path.c_str());
	if (!file.is_open())
		return 500;

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	_response.setBody(buffer.str());
	_response.setHeader("Content-type", utils::getMIME(utils::getFileExtension(full_path)));

	return 200;
}

int Request::processPostRequest()
{
	if (getLocation().upload_enable())
	{
		if (!saveBodyAsFile())
		{
			utils::printMessage("Failed to save POST body to file", COLOR_RED);
			return 500;
		}
		return 201;
	}
	return 403;
}

std::string Request::getPostFilename()
{
	std::string filename;

	if (hasHeader("x-filename"))
		filename = _headers["x-filename"];
	else if (_parameters.count("filename"))
		filename = _parameters["filename"];
	else
	{
		std::string extension = (hasHeader("content-type") ? utils::getExtFromMIME(_headers["content-type"]) : "");
		filename              = "file_" + utils::toString(time(NULL)) + extension;
	}

	return filename;
}

int Request::saveBodyAsFile()
{
	std::string   file_name = getLocation().get_root() + "/" + getLocation().get_upload_pass() + "/" + getPostFilename();

	std::ofstream outFile(file_name.c_str(), std::ios::binary);
	if (!outFile)
	{
		utils::printMessage("Error opening file for writing", COLOR_RED);
		return (0);
	}

	outFile.write(_body.data(), _body.size());
	outFile.close();
	_response.setHeader("Location", "/" + getLocation().get_upload_pass() + "/" + getPostFilename());
	return (1);
}

int Request::processDeleteRequest()
{
	std::string full_path = getLocation().get_root() + getPath();

	if (access(full_path.c_str(), F_OK) != 0)
		return (404);

	struct stat st;
	if (stat(full_path.c_str(), &st) == -1)
		return (500);

	if (S_ISREG(st.st_mode))
	{
		if (std::remove(full_path.c_str()) != 0)
			return (500);
		_response.setBody(_path + " deleted successfully.");
		return (200);
	}
	else
		return (403);
}

bool Request::readChunkedBody()
{
	std::size_t       pos = 0;
	std::vector<char> decoded;

	std::string       bodyStr;
	if (!_body.empty())
		bodyStr.assign(_body.begin(), _body.end());

	if (bodyStr == "0\r\n\r\n" || _body.size() == 0)
	{
		_body.clear();
		return true;
	}

	while (true)
	{
		std::string::size_type endOfSize = bodyStr.find("\r\n", pos);
		if (endOfSize == std::string::npos)
			return false;

		std::string        sizeStr = bodyStr.substr(pos, endOfSize - pos);
		std::istringstream iss(sizeStr);
		std::size_t        chunkSize;
		iss >> std::hex >> chunkSize;

		if (iss.fail())
			return false;

		pos = endOfSize + 2;

		if (chunkSize == 0)
			break;

		if (pos + chunkSize > bodyStr.size())
			return false;

		for (std::size_t i = 0; i < chunkSize; ++i)
		{
			decoded.push_back(bodyStr[pos + i]);
		}

		pos += chunkSize;

		if (pos + 2 > bodyStr.size() || bodyStr.substr(pos, 2) != "\r\n")
			return false;

		pos += 2;
	}

	_body = decoded;
	return true;
}

void Request::splitScriptAndPathInfo(const std::string& path, std::string& script_name, std::string& path_info)
{
	std::vector<std::string> cgi_exts;
	cgi_exts.push_back(".py");
	for (size_t i = 0; i < cgi_exts.size(); ++i)
	{
		size_t ext_pos = path.find(cgi_exts[i]);
		if (ext_pos != std::string::npos)
		{
			script_name = path.substr(0, ext_pos + cgi_exts[i].length());
			path_info   = path.substr(script_name.length());
			return;
		}
	}

	script_name = path;
	path_info   = " ";
}

std::string Request::get_script_filename(const std::string& s_name)
{
	if (!_location->get_root().empty())
	{
		std::string        location_prefix = _location->get_path();
		const std::string& root            = _location->get_root();
		if (root.find(location_prefix) != std::string::npos)
		{
			std::string relative_path = s_name.substr(location_prefix.length());
			if (!relative_path.empty() && relative_path[0] == '/')
				relative_path = relative_path.substr(1);
			return root + "/" + relative_path;
		}
		else
			return root + s_name;
	}
	else
		return _client->getServer()->get_root() + s_name;
}

bool Request::executeCgi()
{
	std::string                        full_path = "./html" + _path;
	std::map<std::string, std::string> env;
	std::string                        s_name;
	std::string                        p_info;

	splitScriptAndPathInfo(_path, s_name, p_info);
	env["REQUEST_METHOD"]    = utils::methodName(_method);
	env["SERVER_PROTOCOL"]   = getProtocol();
	env["QUERY_STRING"]      = _query_string;
	env["SCRIPT_NAME"]       = s_name;
	env["SCRIPT_FILENAME"]   = get_script_filename(s_name);
	env["CONTENT_LENGTH"]    = utils::toString(_content_length);
	env["SERVER_NAME"]       = _client->getServer()->get_server_names()[0];
	env["SERVER_PORT"]       = utils::toString(_client->getServer()->get_listen());
	env["CONTENT_TYPE"]      = utils::getMIME(_content_type);
	env["PATH_INFO"]         = p_info;
	env["GATEWAY_INTERFACE"] = "CGI/1.1";

	_cgi_executor.init(full_path, env, utils::methodName(_method), _content_length);
	_cgi_executor.set_input_cgi(_body);

	if (_cgi_executor.execute(env))
		return false;
	return true;
}

void Request::setKeepAlive(bool is)
{
	_headers["connection"] = (is) ? "keep-alive" : "close";
}

bool Request::isKeepALive()
{
	std::map<std::string, std::string>::const_iterator it = utils::findHeaderCaseInsensitive(_headers, "connection");
	if (it != _headers.end() && (utils::toLowerString1(it->second) == "close"))
		return (false);
	return true;
}

int Request::parseBody()
{
	size_t body_start = _request.find("\r\n\r\n");
	if (body_start == std::string::npos)
		return 400;

	body_start            += 4;
	std::string body_data  = _request.substr(body_start);

	if (_request.size() - body_start > getClient()->getServer()->get_client_max_body_size())
		return 413;

	if (_content_length > 0)
	{
		if (body_data.size() < _content_length)
		{
			_is_valid    = false;
			_parse_error = "Body shorter than Content-Length.";
			return 400;
		}
		if (body_data.size() > _content_length)
			body_data = body_data.substr(0, _content_length);
		_body.assign(body_data.begin(), body_data.begin() + _content_length);
	}

	return 200;
}

void Request::cheak_loaction()
{
	const std::vector<Location>& locations = getClient()->getServer()->get_locations();
	const Location*              matched   = NULL;
	size_t                       max_len   = 0;
	for (size_t i = 0; i < locations.size(); ++i)
	{
		const std::string& loc_path = locations[i].get_path();
		if (_path.find(loc_path) == 0 && loc_path.length() > max_len)
		{
			matched = &locations[i];
			max_len = loc_path.length();
		}
	}
	if (!matched)
		_location = const_cast<Location*>(&locations[0]);
	else
		_location = const_cast<Location*>(matched);
	if (_location->get_cgi_bool())
		_is_cgi = true;
}

bool Request::isAllowedMethod()
{
	const std::vector<std::string> allowed = _location->get_allow_methods();
	if (allowed.size() == 0)
		return true;
	if (std::find(allowed.begin(), allowed.end(), utils::toLowerString1(utils::methodName(_method))) != allowed.end())
		return true;
	return (false);
}

Location& Request::getLocation()
{
	return *_location;
}

std::string& Request::getRequest()
{
	return _request;
}

std::string& Request::getProtocol()
{
	return _protocol;
}

std::vector<char>& Request::getBody()
{
	return _body;
}

void Request::clearRequest()
{
	_method         = UNKNOWN;
	_path           = "";
	_host           = "";
	_query_string   = "";
	_protocol       = "";
	_content_type   = "";
	_parse_error    = "";
	_request        = "";
	_host_port      = 0;
	_content_length = 0;
	_is_cgi         = false;
	_parsedHeaders  = false;
	_keep_alive     = true;
	_is_valid       = true;
	_response.clearResponse();
	_parameters.clear();
	_headers.clear();
	_body.clear();
}

std::map<std::string, std::string>& Request::getParameters()
{
	return _parameters;
}

Client* Request::getClient()
{
	return _client;
}

