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
#include <cstring>
#include <sstream>
#include "Client.hpp"
#include "Channel.hpp"
#include "irc_messages.hpp"

class Client;
class Channel;

class Server
{
	private:
		int				server_fd;
		int		port;
		std::string password;
		static bool g_signal;
		std::vector <struct pollfd> poll_fds;
		std::vector <Client> clients_vector;
		std::string _buffer;
		std::string name;
		std::vector <Channel> channels_vector;


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
		void checkLogIn(std::string buffer, std::string token, int fd);
		bool isNickTaken(const std::string& nick);
		void checkNick(std::string buffer, std::string token, int fd);
		void checkUser(std::string buffer, std::string token, int fd);
		void sendResponse(std::string msg, int fd);


		//new methods!
		void close_client(int fd);

		bool checkRegistration(std::string buffer, std::string token, int fd);

		bool iequalscommands(std::string toke, std::string &buffer);

		bool Channel_already_created(std::string name);

		Channel *getChannel(std::string name);

		Client *getClientByNick(std::string nick);
		Client *getClientByFd(int fd);

		void channelSendResponse(std::string channel, std::string response, int fd);

		void removeChannel(std::string channelName);

		std::string fillmessage(int mesage_type, std::string channelName, int fd);


		//COMMANDS
		void ft_invite(std::string buffer, int fd);
		void ft_join(std::string buffer, int fd);
		void ft_kick(std::string buffer, int fd);
		void ft_list(std::string buffer, int fd);
		void ft_mode(std::string buffer, int fd);
		void ft_part(std::string buffer, int fd);
		void ft_privmsg(std::string buffer, int fd);
		void ft_topic(std::string buffer, int fd);

		void setbuffer(std::string buffer);
		std::string getbuffer();
};

std::string getCommandArg(std::string buffer, const std::string &cmd);
std::string trimLeading(std::string s);
bool iequals(const std::string &a, const std::string &b);
void ft_invite(std::string buffer, int fd);
void ft_join(std::string buffer, int fd);
void ft_list(std::string buffer, int fd);
void ft_kick(std::string buffer, int fd);
void ft_topic(std::string buffer, int fd);
void ft_privmsg(std::string buffer, int fd);
void ft_mode(std::string buffer, int fd);
void ft_part(std::string buffer, int fd);
