#include "../HPP/CGIExecutor.hpp"
#include "../HPP/ServerRun.hpp"

static char** s_env;

CGIExecutor::CGIExecutor()
    : _path("")
    , _envp(NULL)
    , _output()
    , _body()
    , _method("")
    , _response()
    , _total_written(0)
{
	_stdin_fd  = -1;
	_stdout_fd = -1;
	_cgi_pid   = -1;
	_state     = INIT;
}

void CGIExecutor::init(std::string path, std::map<std::string, std::string> env, std::string method, size_t content_length)
{
	_path           = path;
	_method         = method;
	_content_length = content_length;
	_total_written  = 0;
	_stdin_fd       = -1;
	_stdout_fd      = -1;
	_cgi_pid        = -1;
	_state          = INIT;
	_envp           = new char*[env.size() + 1];
	size_t index    = 0;

	for (std::map<std::string, std::string>::iterator it = env.begin(); it != env.end(); it++)
	{
		std::string entry = it->first + "=" + it->second;
		_envp[index]      = strdup(entry.c_str());
		++index;
	}

	_envp[index] = NULL;
}

CGIExecutor::~CGIExecutor()
{
	if (_envp)
	{
		for (int i = 0; _envp && _envp[i] != NULL; i++)
			free(_envp[i]);
		delete[] _envp;
	}
}

bool shouldSendBodyToCgi(const std::string& method, size_t content_length)
{
	return (utils::isEquals(method, "POST") && content_length > 0);
}

int CGIExecutor::execute(const std::map<std::string, std::string> env)
{
	char* _argv[]        = { strdup(env.at("SCRIPT_FILENAME").c_str()), NULL };
	int   pipe_stdin[2]  = { -1, -1 };
	int   pipe_stdout[2] = { -1, -1 };

	int   status         = 0;
	s_env                = _envp;
	if (shouldSendBodyToCgi(_method, _content_length) && (pipe(pipe_stdin) == -1))
		return (-1);
	if (pipe(pipe_stdout) == -1)
		return -1;

	utils::setToNonBlocking(pipe_stdin[1]);
	utils::setToNonBlocking(pipe_stdout[0]);

	pid_t pid = fork();
	if (pid == -1)
	{
		if (pipe_stdin[0] > 0)
			close(pipe_stdin[0]);
		if (pipe_stdin[1] > 0)
			close(pipe_stdin[1]);
		if (pipe_stdout[0] > 0)
			close(pipe_stdout[0]);
		if (pipe_stdout[1] > 0)
			close(pipe_stdout[1]);
		free(_argv[0]);
		return -2;
	}
	_cgi_time = time(NULL);
	if (pid == 0)
	{
		if (shouldSendBodyToCgi(_method, _content_length))
			dup2(pipe_stdin[0], STDIN_FILENO);
		dup2(pipe_stdout[1], STDOUT_FILENO);

		if (pipe_stdin[0] > 0)
			close(pipe_stdin[0]);
		if (pipe_stdin[1] > 0)
			close(pipe_stdin[1]);
		if (pipe_stdout[0] > 0)
			close(pipe_stdout[0]);
		if (pipe_stdout[1] > 0)
			close(pipe_stdout[1]);

		if (access(env.at("SCRIPT_FILENAME").c_str(), X_OK) != 0)
		{
			for (int i = 0; _envp && _envp[i] != NULL; i++)
				free(_envp[i]);
			delete[] _envp;
			free(_argv[0]);
			perror("access");
			close(pipe_stdin[0]);
			close(pipe_stdout[0]);
			if (errno == ENOENT)
				exit(2);
			else if (errno == EACCES)
				exit(13);
			else
				exit(1);
		}
		execve(env.at("SCRIPT_FILENAME").c_str(), _argv, _envp);
		perror("execve");
		for (int i = 0; _envp && _envp[i] != NULL; i++)
			free(_envp[i]);
		delete[] _envp;
		free(_argv[0]);
		if (errno == ENOENT)
			exit(2);
		else if (errno == EACCES)
			exit(13);
		else if (errno == ENOEXEC)
			exit(8);
		else
			exit(1);
	}
	else
	{
		if (pipe_stdin[0] > 0)
			close(pipe_stdin[0]);
		if (pipe_stdout[1] > 0)
			close(pipe_stdout[1]);

		free(_argv[0]);
		_stdin_fd  = pipe_stdin[1];
		_stdout_fd = pipe_stdout[0];
		_cgi_pid   = pid;
		for (int i = 0; _envp && _envp[i] != NULL; i++)
			free(_envp[i]);
		delete[] _envp;
		_envp = NULL;
		waitpid(pid, &status, WNOHANG);
		if (status < 0)
		{
			if (_stdin_fd > 0)
				close(_stdin_fd);
			if (_stdout_fd > 0)
				close(_stdout_fd);
			return 1;
		}
		return 0;
	}
	return (0);
}

void CGIExecutor::readCgiOutput(int cgi_fd)
{
	_state = READING;
	char    buffer[4096];
	ssize_t bytes_read;

	while (true)
	{
		bytes_read = read(cgi_fd, buffer, sizeof(buffer));

		if (bytes_read > 0)
			_output_buffer.insert(_output_buffer.end(), buffer, buffer + bytes_read);
		else
		{
			if (bytes_read == 0 || bytes_read == -1)
			{
				_state = DONE;
				if (_stdout_fd > 0)
					close(_stdout_fd);
				_stdout_fd = -1;
			}
			break;
		}
	}
}

void CGIExecutor::writeToCgiInput(int cgi_fd)
{
	if (shouldSendBodyToCgi(_method, _content_length))
	{
		_state = WRITING;

		while (_total_written < _input_buffer.size())
		{
			ssize_t written = write(cgi_fd, &_input_buffer[_total_written], _input_buffer.size() - _total_written);

			if (written == -1)
				return;

			_total_written += written;
		}
		if (_total_written <= _input_buffer.size())
			_state = READING;
	}
	else
		_state = READING;
}

int CGIExecutor::parseCgiOutput(Response& response)
{
	if (_output_buffer.empty())
		return -1;

	std::string raw_str(_output_buffer.begin(), _output_buffer.end());
	size_t      header_end    = raw_str.find("\r\n\r\n");
	size_t      header_length = 4;

	if (header_end == std::string::npos)
	{
		header_end    = raw_str.find("\n\n");
		header_length = 2;
	}

	if (header_end == std::string::npos)
	{
		response.setBody(_output_buffer);
		return 0;
	}

	std::string headers_str = raw_str.substr(0, header_end);
	parseHeaders(headers_str, response);

	size_t body_start = header_end + header_length;
	if (body_start < _output_buffer.size())
		response.getBody().assign(_output_buffer.begin() + body_start, _output_buffer.end());
	response.setHeader("Content-Length", utils::toString(response.getBody().size()));
	if (response.getHeader("Content-Type").empty())
		response.setHeader("Content-Type", "text/html");
	return (0);
}

void CGIExecutor::parseHeaders(std::string headers_str, Response& response)
{

	std::istringstream iss(headers_str);
	std::string        line;

	while (std::getline(iss, line))
	{
		if (!line.empty() && line[line.length() - 1] == '\r')
			line.erase(line.length() - 1);

		if (line.empty())
			continue;

		size_t colon_pos = line.find(':');
		if (colon_pos != std::string::npos)
		{
			std::string key   = line.substr(0, colon_pos);
			std::string value = line.substr(colon_pos + 1);

			key               = utils::trim(key);
			value             = utils::trim(value);

			if (key == "Status")
			{
				int code = atoi(value.c_str());
				response.setStatusCode(code);
			}
			else
				response.setHeader(key, value);
		}
	}
}

void CGIExecutor::clearCgi()
{
	_path.clear();
	_method.clear();
	_body.clear();
	_output.clear();
	_environment_vars.clear();
	_input_buffer.clear();
	_output_buffer.clear();
	_content_length = 0;
	_total_written  = 0;
	_state          = INIT;
	if (_cgi_pid > 0)
		kill(_cgi_pid, SIGTERM);
	_cgi_pid = -1;
	ServerRun::getInstance().removeCgiFd(_stdin_fd);
	ServerRun::getInstance().removeCgiFd(_stdout_fd);
}

std::vector<char>  CGIExecutor::getOutput() { return _output; };

std::vector<char>& CGIExecutor::getBody() { return _body; };

char**             CGIExecutor::get_env()
{
	return _envp;
}

void CGIExecutor::set_null_env()
{
	_envp = NULL;
}

CGIExecutor& CGIExecutor::setEnvVar(std::string key, std::string value)
{
	_environment_vars[key] = value;
	return *this;
};

time_t CGIExecutor::get_time()
{
	return _cgi_time;
}

int& CGIExecutor::getStdinFd()
{
	return _stdin_fd;
}

int& CGIExecutor::getStdoutFd()
{
	return _stdout_fd;
}

pid_t& CGIExecutor::getCgiPid()
{
	return _cgi_pid;
}

std::vector<char>& CGIExecutor::getInputBuffer()
{
	return _input_buffer;
}

std::vector<char>& CGIExecutor::getOutputBuffer()
{
	return _output_buffer;
}

CGIExecutor::State CGIExecutor::getState()
{
	return _state;
}

void CGIExecutor::set_input_cgi(std::vector<char>& input)
{
	_input_buffer.insert(_input_buffer.end(), input.begin(), input.end());
}