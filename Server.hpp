#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
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
#include "Client.hpp"  // for Client class

class Client; // Forward declaration of Client class

class Server
{
	private:
		std::string password;
		int         port;
		int         server_fd;
		std::vector<struct pollfd> poll_fds;
		std::vector<Client> clients_vector; // map to store clients by their file descriptor
		struct sockaddr_in addr;
		static bool signal_flag; // renamed from 'signal' to avoid shadowing function

		void create_server_socket(void);

	public:
		static void signal_handler(int sig);

		Server(const std::string &port_str, const std::string &password_str);

		void init(void);
		void accept_connection(void);
		void receive_data(int fd);
		void launch(void);
		void close_fds(void);
};

#endif
