#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client 
{
	private:
		int         fd;
		std::string ip;
		int         port;

	public:
		Client(int client_fd, const struct sockaddr_in &addr);
		
		int         get_fd() const;
		std::string get_ip() const;
		int         get_port() const;
};

#endif
