#include "../parse/config_parser.hpp"
#include "./HPP/ServerRun.hpp"

int main(int argc, char* argv[])
{
	std::string confg_file = (argc != 2 ? "./config/server.conf" : argv[1]);
	try
	{
		Config config;
		config.parse(confg_file	);

		ServerRun server_run = ServerRun::getInstance();
		server_run.setServers(config.get_servers());

		server_run.start();

		ServerRun::destroyInstance();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}