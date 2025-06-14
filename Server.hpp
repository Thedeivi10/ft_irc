#pragma once 

#include <string>
#include <sys/socket.h>
#include <vector>
#include <poll.h>
#include <netinet/in.h>
#include <iostream>     // for std::cout, std::endl
#include <cstdlib>      // for std::atoi
#include <cerrno>       // for errno
#include <stdexcept>    // for std::runtime_error
#include <fcntl.h>      // for fcntl, F_SETFL, O_NONBLOCK
#include <unistd.h>     // for close
#include <arpa/inet.h>  // for inet_ntoa, ntohs
#include <csignal>
#include <sstream>
#include "Client.hpp"

class Client;

class Server
{
	private:
		int				server_fd;
		int		port;
		std::string password;
		static bool g_signal;
		std::vector <struct pollfd> poll_fds;
		std::vector <Client> clients_vector;


	public:
		static void signal_handler(int sig);
		Server(std::string const &port, std::string const &password);
		Server();
		~Server();

		Client *getClient(int fd);

		void init();
		void createServerSocket();
		void throw_error(std::string error_msg);
		void launchServer();
		void accept_connection();
		void recieved_data(int fd);
		void proccesCommand(std::string buffer, int fd);
		bool checkLogIn(std::string buffer, std::string token, int fd);
		bool checkNick(std::string buffer, std::string token, int fd);
		bool checkUser(std::string buffer, std::string token, int fd);
		void sendResponse(std::string msg, int fd);
};


