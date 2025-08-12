#include "../../inc/webserv.h"
#include "../HPP/ServerRun.hpp"
#include <csignal>

namespace utils
{

	int setToNonBlocking(int fd)
	{
		if (fd < 0)
			return (0);
		return fcntl(fd, F_SETFL, O_NONBLOCK);
	}

	std::string getMIME(std::string ext)
	{
		std::map<std::string, std::string> mime_types;
		mime_types["html"]    = "text/html";
		mime_types["css"]     = "text/css";
		mime_types["js"]      = "application/javascript";
		mime_types["jpg"]     = "image/jpeg";
		mime_types["png"]     = "image/png";
		mime_types["gif"]     = "image/gif";
		mime_types["txt"]     = "text/plain";
		mime_types["json"]    = "application/json";
		mime_types["xml"]     = "application/xml";
		mime_types["svg"]     = "image/svg+xml";
		mime_types["ico"]     = "image/x-icon";
		mime_types["mp4"]     = "video/mp4";
		mime_types["mp3"]     = "audio/mpeg";
		mime_types["wav"]     = "audio/wav";
		mime_types["pdf"]     = "application/pdf";
		mime_types["zip"]     = "application/zip";
		mime_types["tar"]     = "application/x-tar";
		mime_types["gzip"]    = "application/gzip";

		std::string ext_lower = ext;
		std::transform(ext_lower.begin(), ext_lower.end(), ext_lower.begin(), ::tolower);

		if (mime_types.find(ext_lower) != mime_types.end())
			return mime_types[ext_lower];

		return "application/octet-stream";
	}

	std::string getFileExtension(std::string path)
	{
		size_t pos = path.find_last_of('.');
		if (pos != std::string::npos)
			return path.substr(pos + 1);
		return "";
	}

	std::string getHttpDate()
	{
		std::time_t now = std::time(NULL);
		std::tm     gmt = *std::gmtime(&now);

		char        buffer[100];
		std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", &gmt);
		return buffer;
	}

	void printMessage(std::string msg, std::string col)
	{
		std::time_t now       = std::time(0);
		std::tm*    localTime = std::localtime(&now);

		// Format time as [HH:MM:SS]
		char        timeStr[9];
		std::strftime(timeStr, sizeof(timeStr), "%H:%M:%S", localTime);

		// Print formatted message
		std::cout << "[" << timeStr << "] " << col << msg << COLOR_RESET << std::endl;
	}

	void displayProgressBar(size_t sent, size_t total)
	{
		const int barWidth = 50;
		float     progress = static_cast<float>(sent) / total;
		int       pos      = static_cast<int>(barWidth * progress);

		std::cout << "\r[";
		for (int i = 0; i < barWidth; ++i)
		{
			if (i < pos)
				std::cout << "=";
			else if (i == pos)
				std::cout << ">";
			else
				std::cout << " ";
		}
		std::cout << "] " << int(progress * 100.0) << " %";
		std::cout.flush();
		std::cout << std::endl;
	}

	std::string trim(const std::string& str)
	{
		std::string::size_type start = str.find_first_not_of(" \t");
		if (start == std::string::npos)
			return "";

		std::string::size_type end = str.find_last_not_of(" \t");
		return str.substr(start, end - start + 1);
	}

	std::string methodName(int n)
	{
		if (n == 0)
			return "GET";
		if (n == 1)
			return "POST";
		if (n == 2)
			return "DELETE";
		return "NON";
	}

	std::string& toLowerString(std::string& str)
	{
		for (std::string::iterator it = str.begin(); it != str.end(); ++it)
			*it = static_cast<char>(tolower(static_cast<unsigned char>(*it)));
		return (str);
	}

	std::string toLowerString1(std::string str)
	{
		for (std::string::iterator it = str.begin(); it != str.end(); ++it)
			*it = static_cast<char>(tolower(static_cast<unsigned char>(*it)));
		return (str);
	}

	std::string toUpperCase(std::string str)
	{
		for (std::string::iterator it = str.begin(); it != str.end(); ++it)
			*it = static_cast<char>(toupper(static_cast<unsigned char>(*it)));
		return (str);
	}

	bool is_regular_file(const std::string& path)
	{
		struct stat path_stat;
		if (stat(path.c_str(), &path_stat) != 0)
			return false;
		return S_ISREG(path_stat.st_mode);
	}

	bool isEquals(const std::string& a, const std::string& b)
	{
		if (a.size() != b.size())
			return false;

		for (std::string::size_type i = 0; i < a.size(); ++i)
		{
			if (std::tolower(a[i]) != std::tolower(b[i]))
				return false;
		}
		return true;
	}

	std::map<std::string, std::string>::const_iterator
	findHeaderCaseInsensitive(const std::map<std::string, std::string>& headers, const std::string& key)
	{
		std::map<std::string, std::string>::const_iterator it = headers.begin();
		for (; it != headers.end(); ++it)
		{
			if (isEquals(it->first, key))
				break;
		}
		return it;
	}

	void printMap(const std::map<std::string, std::string> _map)
	{
		std::map<std::string, std::string>::const_iterator it = _map.begin();
		printMessage("--------------- HEADERS ---------------", COLOR_RED);
		for (; it != _map.end(); it++)
		{
			utils::printMessage(it->first + " : " + it->second, COLOR_RED);
		}
		printMessage("--------------- HEADERS ---------------", COLOR_RED);
	}

	std::string removeLocationFromPath(std::string location, std::string path)
	{
		if (!location.empty() && location[location.size() - 1] == '/')
			location.erase(location.size() - 1);

		std::string relative_path;
		if (path.find(location + "/") == 0)
			relative_path = path.substr(location.length() + 1);
		else
			relative_path = path;

		return relative_path;
	}

	bool isRequestLineValid(const std::string& request)
	{
		size_t pos = request.find("\r\n");
		if (pos == std::string::npos)
			return false;

		std::string request_line = request.substr(0, pos);
		size_t      first_space  = request_line.find(' ');
		size_t      second_space = request_line.find(' ', first_space + 1);
		if (first_space == std::string::npos || second_space == std::string::npos)
			return false;

		return true;
	}

	std::string extractHostname(const std::string& host_header)
	{
		size_t colon_pos = host_header.find(':');
		if (colon_pos != std::string::npos)
			return host_header.substr(0, colon_pos);
		return host_header;
	}

	void sig_handler(int sig)
	{
		if (sig == SIGINT)
		{
			ServerRun::getInstance().stopServer();
			ServerRun::getInstance().destroyInstance();
			exit(sig);
		}
	}

	void setProperStatusCodeBody(int exit_code, int& s_code, std::string& body)
	{
		switch (exit_code)
		{
			case 0:
				s_code = 200; // OK
				body.clear();
				break;
			case 1:
				s_code = 500;
				body   = "Internal Server Error";
				break;
			case 2:
				s_code = 404;
				body   = "Not Found";
				break;
			case 8:
				s_code = 500;
				body   = "Exec Format Error";
				break;
			case 13:
				s_code = 403;
				body   = "Permission Denied";
				break;
			case 126:
				s_code = 500;
				body   = "Command Invoked Cannot Execute";
				break;
			case 127:
				s_code = 404;
				body   = "Command Not Found";
				break;
			case 128:
				s_code = 500;
				body   = "Invalid Exit Argument";
				break;
			case 130:
				s_code = 500;
				body   = "Terminated by SIGINT (Ctrl+C)";
				break;
			case 137:
				s_code = 500;
				body   = "Killed (SIGKILL)";
				break;
			case 139:
				s_code = 500;
				body   = "Segmentation Fault (SIGSEGV)";
				break;
			case 143:
				s_code = 500;
				body   = "Terminated (SIGTERM)";
				break;
			case 255:
				s_code = 500;
				body   = "Exit Status Out of Range";
				break;
			default:
				s_code = 500;
				body   = "Unknown Error (exit code " + toString(exit_code) + ")";
				break;
		}
	}

	std::string getExtFromMIME(std::string header)
	{
		header = toLowerString(header);

		if (header == "text/plain")
			return ".txt";
		if (header == "text/html")
			return ".html";
		if (header == "text/css")
			return ".css";
		if (header == "text/javascript" || header == "application/javascript")
			return ".js";
		if (header == "image/jpeg")
			return ".jpg";
		if (header == "image/png")
			return ".png";
		if (header == "image/gif")
			return ".gif";
		if (header == "image/webp")
			return ".webp";
		if (header == "image/svg+xml")
			return ".svg";
		if (header == "image/bmp")
			return ".bmp";
		if (header == "image/x-icon")
			return ".ico";
		if (header == "application/json")
			return ".json";
		if (header == "application/pdf")
			return ".pdf";
		if (header == "application/xml")
			return ".xml";
		if (header == "application/zip")
			return ".zip";
		if (header == "application/x-tar")
			return ".tar";
		if (header == "application/x-rar-compressed")
			return ".rar";
		if (header == "application/gzip" || header == "application/x-gzip")
			return ".gz";
		if (header == "audio/mpeg")
			return ".mp3";
		if (header == "audio/wav")
			return ".wav";
		if (header == "audio/ogg")
			return ".ogg";
		if (header == "audio/webm")
			return ".webm";
		if (header == "video/mp4")
			return ".mp4";
		if (header == "video/x-msvideo")
			return ".avi";
		if (header == "video/x-matroska")
			return ".mkv";
		if (header == "video/webm")
			return ".webm";
		if (header == "application/octet-stream")
			return ".bin";

		return ".bin";
	}
}; // namespace utils