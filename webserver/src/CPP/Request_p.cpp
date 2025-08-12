#include "../HPP/Request.hpp"

char from_hex(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return 0;
}

std::string url_decode(const std::string& in)
{
	std::string out;
	for (size_t i = 0; i < in.size(); ++i)
	{
		if (in[i] == '%' && i + 2 < in.size())
		{
			char decoded  = (from_hex(in[i + 1]) << 4) | from_hex(in[i + 2]);
			out          += decoded;
			i            += 2;
		}
		else if (in[i] == '+')
		{
			out += ' ';
		}
		else
		{
			out += in[i];
		}
	}
	return out;
}

bool is_valid_method_char(char c)
{
	return std::isalpha(c) || std::isdigit(c) || c == '!' || c == '#' || c == '$' || c == '%' || c == '&' || c == '\'' || c == '*' || c == '+' || c == '-' || c == '.' || c == '^' || c == '_' || c == '`' || c == '|' || c == '~';
}

bool is_valid_target_char(char c)
{
	return std::isalnum(c) || c == '/' || c == '.' || c == '-' || c == '_' || c == '?' || c == '=' || c == '&' || c == '%' || c == ':' || c == '@' || c == '!' || c == '~' || c == '*' || c == '\'' || c == '(' || c == ')' || c == ',' || c == '$';
}

bool is_valid_http_version(const std::string& ver)
{
	return ver == "HTTP/1.1" || ver == "HTTP/1.0";
}

bool Request::parseRequestLine(std::string& method_str)
{

	for (size_t i = 0; i < method_str.size(); i++)
	{
		if (!is_valid_method_char(method_str[i]))
			return false;
	}

	for (size_t i = 0; i < _path.size(); i++)
	{
		if (!is_valid_target_char(_path[i]))
			return false;
	}

	if (!is_valid_http_version(_protocol))
		return false;

	_parameters.clear();

	std::istringstream stream(_query_string);
	std::string        pair;

	while (std::getline(stream, pair, '&'))
	{
		size_t      eq = pair.find('=');
		std::string key, value;

		if (eq != std::string::npos)
		{
			key   = url_decode(pair.substr(0, eq));
			value = url_decode(pair.substr(eq + 1));
		}
		else
		{
			key   = url_decode(pair);
			value = "";
		}

		_parameters[key] = value;
	}

	return true;
}

bool is_valid_token_char(char c)
{
	return std::isalpha(c) || std::isdigit(c) || c == '!' || c == '#' || c == '$' || c == '%' || c == '&' || c == '\'' || c == '*' || c == '+' || c == '-' || c == '.' || c == '^' || c == '_' || c == '`' || c == '|' || c == '~';
}

bool is_valid_header_name(const std::string& name, std::string& error_message)
{
	if (name.empty())
	{
		error_message = "Header name is empty.";
		return false;
	}

	for (size_t i = 0; i < name.length(); ++i)
	{
		if (!is_valid_token_char(name[i]))
		{
			std::ostringstream oss;
			oss << "Invalid character in header name: '" << name[i]
			    << "' (ASCII " << static_cast<int>(name[i]) << ")";
			error_message = oss.str();
			return false;
		}
	}

	return true;
}

bool is_valid_header_value(const std::string& value, std::string& error)
{
	for (size_t i = 0; i < value.length(); ++i)
	{
		char c = value[i];
		if ((c < 32 && c != '\t') || c == 127)
		{
			std::ostringstream oss;
			oss << "Invalid character in header value: ASCII " << (int)c;
			error = oss.str();
			return false;
		}
	}
	return true;
}

bool is_valid_content_length(const std::string& value)
{
	for (size_t i = 0; i < value.length(); ++i)
	{
		if (!std::isdigit(value[i]))
			return false;
	}
	return true;
}

bool is_valid_user_agent(const std::string& value)
{
	for (size_t i = 0; i < value.length(); ++i)
	{
		char c = value[i];
		if ((c < 0x20 && c != '\t') || c > 0x7E)
			return false;
	}
	return true;
}

bool is_valid_accept_encoding(const std::string& value)
{
	size_t i = 0, len = value.length();
	while (i < len)
	{
		while (i < len && value[i] == ' ')
			++i;
		size_t start = i;
		if (i < len && value[i] == '*')
			++i;
		else
			while (i < len && (std::isalnum(static_cast<unsigned char>(value[i])) || value[i] == '-'))
				++i;
		if (i == start)
			return false;
		while (i < len && value[i] == ' ')
			++i;
		if (i < len && value[i] == ';')
		{
			++i;
			while (i < len && value[i] == ' ')
				++i;
			if (i + 1 < len && value[i] == 'q' && value[i + 1] == '=')
			{
				i             += 2;
				size_t qstart  = i;
				while (i < len && (std::isdigit(value[i]) || value[i] == '.'))
					++i;
				if (qstart == i)
					return false;
			}
			else
				return false;
		}
		while (i < len && value[i] == ' ')
			++i;
		if (i == len)
			return true;
		if (value[i] != ',')
			return false;
		++i;
	}
	return true;
}

bool is_valid_origin(const std::string& value)
{
	return value.find("http://") == 0 || value.find("https://") == 0;
}

bool is_all_digits(const std::string& s)
{
	if (s.empty())
		return false;
	for (size_t i = 0; i < s.length(); ++i)
		if (!std::isdigit(static_cast<unsigned char>(s[i])))
			return false;
	return true;
}

bool parse_host_header(const std::string& value, std::string& host, std::string& port)
{
	host.clear();
	port.clear();
	if (value.empty())
		return false;

	if (value[0] == '[')
	{
		size_t end = value.find(']');
		if (end == std::string::npos)
			return false;
		host = value.substr(0, end + 1);
		if (end + 1 < value.length())
		{
			if (value[end + 1] != ':')
				return false;
			port = value.substr(end + 2);
			if (!is_all_digits(port))
				return false;
		}
	}
	else
	{
		size_t colon = value.find(':');
		if (colon != std::string::npos)
		{
			host = value.substr(0, colon);
			port = value.substr(colon + 1);
			if (!is_all_digits(port))
				return false;
		}
		else
		{
			host = value;
		}
	}
	if (host.empty())
		return false;
	for (size_t i = 0; i < host.length(); ++i)
	{
		char c = host[i];
		if (c <= 0x20 || c == 0x7F)
			return false;
	}
	return true;
}

bool is_valid_authorization(const std::string& value)
{
	return value.find("Basic ") == 0 || value.find("Bearer ") == 0;
}

std::string to_lower(const std::string& str)
{
	std::string out = str;
	for (size_t i = 0; i < out.length(); ++i)
		out[i] = std::tolower(out[i]);
	return out;
}

bool Request::parse_headers_from_request_string()
{
	size_t headers_start       = _request.find("\r\n"); 
	bool   content_length_seen = false;
	bool   host_seen           = false;
	if (headers_start == std::string::npos)
	{
		_is_valid    = false;
		_parse_error = "Malformed request line or missing CRLF";
		return false;
	}

	headers_start      += 2;

	size_t headers_end  = _request.find("\r\n\r\n", headers_start);
	if (headers_end == std::string::npos)
	{
		_is_valid    = false;
		_parse_error = "Headers not terminated properly";
		return false;
	}

	std::string        headers_block = _request.substr(headers_start, headers_end - headers_start);
	std::istringstream header_stream(headers_block);
	std::string        line;

	while (std::getline(header_stream, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		size_t colon_pos = line.find(':');
		if (colon_pos == std::string::npos)
		{
			_is_valid    = false;
			_parse_error = "Invalid header format: missing ':' in line [" + line + "]";
			return false;
		}

		if (isspace(line[colon_pos - 1]))
		{
			_is_valid    = false;
			_parse_error = "Invalid header format: space before ':' in line [" + line + "]";
			return false;
		}
		std::string name  = line.substr(0, colon_pos);
		std::string value = line.substr(colon_pos + 1);

		name              = utils::trim(name);
		value             = utils::trim(value);
		std::string error_message;
		if (!is_valid_header_name(name, error_message) || !is_valid_header_value(value, error_message))
		{
			_is_valid    = false;
			_parse_error = "Header error in '" + name + "': " + error_message;
			return false;
		}
		name = to_lower(name);
		if (name == "content-length")
		{
			if (content_length_seen)
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' duplicate content-length";
				return false;
			}
			if (!is_valid_content_length(value))
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' not diget";
				return false;
			}
			content_length_seen = true;
			_content_length     = atoi(value.c_str());
		}
		else if (name == "content-type")
		{
			_content_type = value;
		}
		else if (name == "connection")
		{
			std::string lower_value = to_lower(value);
			if (lower_value == "close")
				_keep_alive = false;
		}
		else if (name == "user-agent")
		{
			if (!is_valid_user_agent(value))
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' is not valid user_agent";
				return false;
			}
		}
		else if (name == "authorization")
		{
			if (value.find(' ') == std::string::npos)
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' missing space";
				return false;
			}
			size_t pos = value.find_first_of(" ");
			if (value.find(' ', pos + 1) != std::string::npos)
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' more the one space";
				return false;
			}
			if (!is_valid_authorization(value))
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' is not a valid authorization";
				return false;
			}
		}
		else if (name == "accept-encoding")
		{
			if (!is_valid_accept_encoding(value))
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' is not a valid accept_encoding";
				return false;
			}
		}
		else if (name == "origin")
		{
			if (!is_valid_origin(value))
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' is not a valid origin";
				return false;
			}
		}
		else if (name == "host")
		{
			if (host_seen)
			{
				_is_valid    = false;
				_parse_error = "Header error in '" + value + "' duplicate hoste 1";
				return false;
			}
			host_seen = true;
			_host     = value;
		}
		_headers[name] = value;
	}

	if (_headers.find("host") == _headers.end())
	{
		_is_valid    = false;
		_parse_error = "Missing required 'Host' header.";
		return false;
	}

	_parsedHeaders = true;
	return true;
}

int Request::parseRequest()
{

	size_t header_end = _request.find("\r\n\r\n");
	if (header_end == std::string::npos)
		return 400;

	std::string headers_part = _request.substr(0, header_end);

	size_t      line_end     = headers_part.find("\r\n");
	std::string request_line = headers_part.substr(0, line_end);

	size_t      first_space  = request_line.find(' ');
	if (first_space == std::string::npos)
		return (400);

	size_t second_space = request_line.find(' ', first_space + 1);
	if (second_space == std::string::npos)
	{
		return (400);
	}
	if (request_line.find(' ', second_space + 1) != std::string::npos)
	{
		return (400);
	}
	std::string method_str = request_line.substr(0, first_space);
	std::string target     = request_line.substr(first_space + 1, second_space - first_space - 1);
	_protocol              = request_line.substr(second_space + 1);

	size_t qmark           = target.find('?');

	if (qmark == std::string::npos)
	{
		_path         = target;
		_query_string = "";
	}
	else
	{
		_path         = target.substr(0, qmark);
		_query_string = target.substr(qmark + 1);
	}

	if (!parseRequestLine(method_str))
		return 400;

	if (method_str == "GET")
		_method = GET;
	else if (method_str == "POST")
		_method = POST;
	else if (method_str == "DELETE")
		_method = DELETE;
	else
		_method = UNKNOWN;

	if (!headersParsed())
	{
		if (!parse_headers_from_request_string())
			return 400;
	}
	int ret = parseBody();

	cheak_loaction();
	return ret;
}