#include "../HPP/Response.hpp"
#include <utility>

Response& Response::setBody(std::vector<char> body)
{
	_body.clear();
	_body.assign(body.begin(), body.end());
	setHeader("Content-Length", utils::toString(_body.size()));
	return (*this);
}

void Response::setDefaultHeaders()
{
	setHeader("Server", "Webserv/0.1")
	    .setHeader("Date", utils::getHttpDate())
	    .setHeader("Connection", "keep-alive")
	    .setHeader("Content-Length", "0")
	    .setProtocol("HTTP/1.1");
}

Response& Response::setBody(std::string body)
{
	_body.clear();
	_body.insert(_body.end(), body.begin(), body.end());
	setHeader("Content-Length", utils::toString(_body.size()));
	return (*this);
}

std::string Response::gatherResponseHeaders()
{
	std::string headers = "HTTP/1.1 " + utils::toString(_status_code) + " " + _status_message + "\r\n";
	std::map<std::string, std::string>::const_iterator it;

	for (it = _headers.begin(); it != _headers.end(); ++it)
		headers += it->first + ": " + it->second + "\r\n";

	headers += "\r\n";

	return (headers);
}

void Response::clearResponse()
{
	_protocol           = "";
	_status_message     = "";
	_status_code        = 0;
	_is_sending_headers = true;
	_is_sending_body    = false;
	_is_all_data_sent   = false;
	_body_offset        = 0;
	_header_offset      = 0;
	_headers.clear();
	_body.clear();
}

Response::Response()
{
	clearResponse();
}

std::string Response::getProtocol()
{
	return _protocol;
}

std::string& Response::getStatusMessage()
{
	return _status_message;
}

int Response::getStatusCode()
{
	return _status_code;
}

std::string Response::getHeader(std::string key)
{
	return _headers[key];
}

std::vector<char>& Response::getBody()
{
	return _body;
}

bool Response::isSendingHeaders()
{
	return _is_sending_headers;
}

bool Response::isSendingBody()
{
	return _is_sending_body;
}

size_t Response::getBodyOffset()
{
	return _body_offset;
}

int Response::getHeadersOffset()
{
	return _header_offset;
}

void Response::setIsSendingHeaders(bool is)
{
	_is_sending_headers = is;
}

void Response::setIsSendingBody(bool is)
{
	_is_sending_body = is;
}

void Response::setHeadersOffset(int offset)
{
	_header_offset = offset;
}

void Response::setBodyOffset(int offset)
{
	_body_offset = offset;
}

void Response::setAllDataSent(bool is)
{
	if (is)
		clearResponse();
	_is_all_data_sent = is;
}

bool Response::isAllDataSent()
{
	if (_is_all_data_sent)
	{
		clearResponse();
		return true;
	}
	return false;
}

Response& Response::setProtocol(std::string protocol)
{
	_protocol = protocol;
	return *this;
};

Response& Response::setHeader(std::string key, std::string value)
{
	_headers[key] = value;
	return *this;
};

bool Response::isResponseStarted()
{
	return isSendingBody();
}

int Response::prepareBadRequest(Server* server)
{
	setProtocol("HTTP/1.1")
	    .setStatusCode(400)
	    .checkCustomErrorPage(server);
	return (-1);
}

int Response::handleRedirection(std::pair<int, std::string> redirect)
{
	setStatusCode(redirect.first)
	    .setHeader("Location", redirect.second);
	return (0);
}

int Response::sendResponse(int fd)
{
	ssize_t byte_sent = 0;

	if (isSendingHeaders())
	{
		std::string headers = gatherResponseHeaders();
		while (getHeadersOffset() < (int)headers.size())
		{
			byte_sent = send(fd, headers.c_str() + getHeadersOffset(), headers.size() - getHeadersOffset(), MSG_NOSIGNAL);
			if (byte_sent < 0)
				return 1; // retry...

			setHeadersOffset(getHeadersOffset() + byte_sent);
		}
		setIsSendingHeaders(false);
	}

	// int total_size = getBody().size();
	while (getBodyOffset() < getBody().size())
	{
		byte_sent = send(fd, getBody().data() + getBodyOffset(), getBody().size() - getBodyOffset(), MSG_NOSIGNAL);
		if (byte_sent < 0)
			return 1; // retry...

		setBodyOffset(getBodyOffset() + byte_sent);
		// utils::displayProgressBar(getBodyOffset(), total_size);
	}

	if (getBodyOffset() == getBody().size())
	{
		setAllDataSent(true);
		// utils::printMessage("Response Fully Sent ! to  : " + utils::toString(fd), COLOR_GREEN);
	}

	return 0;
}

void Response::checkCustomErrorPage(Server* server)
{
	if (_status_code < 400 || !server)
		return;

	std::map<int, std::string>::const_iterator it = server->get_error_pages().find(_status_code);
	if (it == server->get_error_pages().end())
		return;

	std::string errorUri = it->second;
	if (errorUri.empty())
		return;

	std::string   fullPath = server->get_root() + errorUri;
	std::ifstream f(fullPath.c_str());
	if (!f.is_open())
		return;

	std::ostringstream ss;
	ss << f.rdbuf();
	std::string body = ss.str();

	this->setBody(body);
	this->setHeader("Content-Type", utils::getMIME(utils::getFileExtension(fullPath)));

	this->setHeader("Content-Length", utils::toString(body.size()));
}

Response& Response::setStatusCode(int code)
{
	_status_code = code;
	switch (code)
	{
		case 100:
			_status_message = "Continue";
			break;
		case 101:
			_status_message = "Switching Protocols";
			break;

		case 200:
			_status_message = "OK";
			break;
		case 201:
			_status_message = "Created";
			break;
		case 202:
			_status_message = "Accepted";
			break;
		case 203:
			_status_message = "Non-Authoritative Information";
			break;
		case 204:
			_status_message = "No Content";
			break;
		case 205:
			_status_message = "Reset Content";
			break;
		case 206:
			_status_message = "Partial Content";
			break;

		case 300:
			_status_message = "Multiple Choices";
			break;
		case 301:
			_status_message = "Moved Permanently";
			break;
		case 302:
			_status_message = "Found";
			break;
		case 303:
			_status_message = "See Other";
			break;
		case 304:
			_status_message = "Not Modified";
			break;
		case 307:
			_status_message = "Temporary Redirect";
			break;
		case 308:
			_status_message = "Permanent Redirect";
			break;

		case 400:
			_status_message = "Bad Request";
			break;
		case 401:
			_status_message = "Unauthorized";
			break;
		case 402:
			_status_message = "Payment Required";
			break;
		case 403:
			_status_message = "Forbidden";
			break;
		case 404:
			_status_message = "Not Found";
			break;
		case 405:
			_status_message = "Method Not Allowed";
			break;
		case 406:
			_status_message = "Not Acceptable";
			break;
		case 408:
			_status_message = "Request Timeout";
			break;
		case 409:
			_status_message = "Conflict";
			break;
		case 410:
			_status_message = "Gone";
			break;
		case 411:
			_status_message = "Length Required";
			break;
		case 413:
			_status_message = "Payload Too Large";
			break;
		case 414:
			_status_message = "URI Too Long";
			break;
		case 415:
			_status_message = "Unsupported Media Type";
			break;
		case 417:
			_status_message = "Expectation Failed";
			break;
		case 418:
			_status_message = "I'm a teapot";
			break; // Easter egg

		case 426:
			_status_message = "Upgrade Required";
			break;

		case 500:
			_status_message = "Internal Server Error";
			break;
		case 501:
			_status_message = "Not Implemented";
			break;
		case 502:
			_status_message = "Bad Gateway";
			break;
		case 503:
			_status_message = "Service Unavailable";
			break;
		case 504:
			_status_message = "Gateway Timeout";
			break;
		case 505:
			_status_message = "HTTP Version Not Supported";
			break;

		default:
			_status_message = "Unknown Status";
			break;
	}
	if (_body.empty())
		setDefaultBody();
	return *this;
}

void Response::setDefaultBody()
{
	std::string color;
	std::string title;
	std::string message;

	int         status_class = _status_code / 100;

	switch (status_class)
	{
		case 1:
			color = "#17a2b8";
			break;
		case 2:
			color = "#28a745";
			break;
		case 3:
			color = "#007bff";
			break;
		case 4:
			color = "#dc3545";
			break;
		case 5:
			color = "#fd7e14";
			break;
		default:
			color = "#6c757d";
			break;
	}

	title            = utils::toString(_status_code) + " " + _status_message;
	message          = _status_message;

	std::string html = "<html><head><title>" + title + "</title>"
	                                                   "<style>"
	                                                   "body { font-family: Arial, sans-serif; background: #f8f9fa; color: #212529; padding: 2em; }"
	                                                   "h1 { color: "
	    + color + "; font-size: 3em; margin-bottom: 0; }"
	              "p { font-size: 1.5em; margin-top: 0; }"
	              "</style>"
	              "</head><body>"
	              "<h1>"
	    + title + "</h1>"
	              "<p>"
	    + message + "</p>"
	                "</body></html>";
	setBody(html);
}

Response::~Response()
{
}