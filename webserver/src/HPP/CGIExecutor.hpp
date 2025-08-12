#ifndef CGIEXECUTOR_HPP
#define CGIEXECUTOR_HPP

#include "../../inc/webserv.h"
#include "Response.hpp"
#include <cstddef>
#include <vector>

class CGIExecutor
{
  public:
	enum State
	{
		INIT,
		READY,
		WRITING,
		READING,
		DONE,
		ERROR
	};

	CGIExecutor();
	void init(std::string path, std::map<std::string, std::string> env, std::string method, size_t content_length);
	~CGIExecutor();
	int                execute(std::map<std::string, std::string> env);
	std::vector<char>  getOutput();
	int                parseCgiOutput(Response& response);
	void               parseHeaders(std::string headers_str, Response& response);
	std::vector<char>& getBody();
	void               clearCgi();
	char**             get_env();
	void               set_null_env();
	CGIExecutor&       setEnvVar(std::string key, std::string value);
	time_t             get_time();
	int&               getStdinFd();
	int&               getStdoutFd();
	pid_t&             getCgiPid();
	std::vector<char>& getInputBuffer();
	std::vector<char>& getOutputBuffer();
	State              getState();
	void               set_input_cgi(std::vector<char>& input);
	void               readCgiOutput(int cgi_fd);
	void               writeToCgiInput(int cgi_fd);

  private:
	std::string                        _path;
	char**                             _envp;
	std::map<std::string, std::string> _environment_vars;
	std::vector<char>                  _output;
	std::vector<char>                  _body;
	std::string                        _method;
	size_t                             _content_length;

	Response                           _response;
	int                                _stdin_fd;
	int                                _stdout_fd;
	int                                _cgi_pid;
	std::vector<char>                  _input_buffer;
	std::vector<char>                  _output_buffer;
	State                              _state;
	time_t                             _cgi_time;
	std::size_t                        _total_written;
};

#endif