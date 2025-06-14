#include "Server.hpp"

bool Server::g_signal = false;

void Server::signal_handler(int sig)
{
	(void)sig;
	std::cout << "Signal recieved!\n";
	g_signal = true;

}

Server::Server()
{
	this->port = 0;
	this->password = "";
}

Server::~Server()
{
}

void Server::throw_error(std::string error_msg)
{
	throw std::runtime_error(error_msg);
}

void Server::createServerSocket()
{
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	int opt = 1;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd == -1)
		throw_error("Failed to create socket!");
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		throw_error("Failed to set socket to reuse mode");
	if (fcntl(server_fd, F_SETFL, O_NONBLOCK) == -1)
		throw_error("Failed to set socket to non-block mode!");
	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		throw_error("Failed to bind socket");
	if (listen(server_fd, SOMAXCONN) == -1)
		throw_error("Failed to set socket in listen state!");

	struct pollfd new_fd;

	new_fd.fd = server_fd;
	new_fd.events = POLLIN;
	new_fd.revents = 0;
	poll_fds.push_back(new_fd);
}

Server::Server(std::string const &port, std::string const &password)
{
	this->port = std::atoi(port.c_str());
	this->password = password;
}

void Server::accept_connection()
{
	struct sockaddr_in cli_addr;
	socklen_t len = sizeof(cli_addr);

	int client_fd = accept(server_fd, (struct sockaddr *)&cli_addr, &len);
	if (client_fd == -1)
		throw_error("Failed to accept client");
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		throw_error("Failed to set client to non-block mode!");

	struct pollfd new_fd;
	new_fd.fd = client_fd;
	new_fd.events = POLLIN;
	new_fd.revents = 0;
	poll_fds.push_back(new_fd);

	Client client(client_fd, inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
	clients_vector.push_back(client);
	std::cout << "Connection has been accetpted! to ip: " <<  inet_ntoa(cli_addr.sin_addr) << std::endl;
	
}

Client *Server::getClient(int fd)
{
	for (size_t i = 0; i < clients_vector.size(); i++)
	{
		if (clients_vector[i].getClifd() == fd)
			return (&clients_vector[i]);
	}
	return NULL;
}

void Server::sendResponse(std::string msg, int fd)
{
	msg = msg + '\n';
	if (send(fd, msg.c_str(), sizeof(msg), 0) == -1)
		throw_error("Failed to send response!");
}

bool Server::checkLogIn(std::string buffer, std::string token, int fd)
{
	Client *client = getClient(fd);

	if (!client)
		throw_error("Error!");
	if (token == "PASS" || token == "pass")
	{
		if (client->getlogIn())
			return (sendResponse("You have already log in!", fd), true);
		buffer.erase(0, 4);
		size_t pos = buffer.find_first_not_of(" \t\n");
		if (pos == std::string::npos)
		{
			sendResponse("Invalid password1!", fd);
			return false;
		}
		buffer.erase(0, pos);
		buffer.erase(buffer.size() - 1);
		if (buffer == this->password)	
			client->setlogIn(true);
		else
		{
			sendResponse("Invalid password2!", fd);
			return false;
		}
	}
	if (!client->getlogIn())
		return false;
	return (true);
}

bool Server::checkNick(std::string buffer, std::string token, int fd)
{
	Client *client = getClient(fd);

	if (!client)
		throw_error("Error!");
	if (token == "NICK" || token == "nick")
	{
		buffer.erase(0, 4);
		size_t pos = buffer.find_first_not_of(" \t\n");
		if (pos == std::string::npos)
		{
			sendResponse("Invalid nick!", fd);
			return false;
		}
		buffer.erase(0, pos);
		client->setNickName(buffer);
	}
	if (client->getNickName() == "")
		return false;
	if (client->getUserName() != "" && client->getNickName() !=)
	return true;
}

bool Server::checkUser(std::string buffer, std::string token, int fd)
{
	Client *client = getClient(fd);

	if (!client)
		throw_error("Error!");
	if (token == "USER" || token == "user")
	{
		buffer.erase(0, 4);
		size_t pos = buffer.find_first_not_of(" \t\n");
		if (pos == std::string::npos)
		{
			sendResponse("Invalid user!", fd);
			return false;
		}
		buffer.erase(0, pos);
		client->setUserName(buffer);
	}
	if (client->getUserName() == "")
		return false;
	return true;
}

void Server::proccesCommand(std::string buffer, int fd)
{
	Client *client = getClient(fd);
	std::string token;
	std::istringstream iss(buffer);

	iss >> token;

	if (token == "pass")
	{
		if (!checkLogIn(buffer, token, fd))
		{
			sendResponse("You haven't log in yet!", fd);
			return;
		}
		return ;
	}
	else if (token == "user")
	{
		if (!checkUser(buffer, token, fd))
		{
			sendResponse("You haven't user yet!", fd);
			return ;
		}
		return ;
	}
	else if (token == "nick")
	{
		if (!checkNick(buffer, token, fd))
		{
			sendResponse("You haven't nickname yet!", fd);
			return ;
		}
		return ;
	}
	
	if (!client->getlogIn())
	{
		sendResponse("You haven't log in yet!", fd);
		return ;
	}
	else if (!client->getRegistered())
	{
		sendResponse("You haven't register yet!", fd);
		return ;
	}
	std::string msg = "Welcome to the server " + client->getUserName();
	sendResponse(msg, fd);
}

void Server::recieved_data(int fd)
{
	char buffer[1024];
	ssize_t bytes_read = recv(fd, buffer, sizeof(buffer) - 1, 0);
	if (bytes_read == -1)
		throw_error("Failed to recieved data!");
	if (bytes_read == 0)
	{
		std::cout << "Client has been desconnected " << fd << std::endl;
		close(fd);
		return ;
	}
	buffer[bytes_read] = '\0';
	proccesCommand(buffer, fd);
}

void Server::launchServer()
{
	while (!g_signal)
	{
		if (poll(&poll_fds[0], poll_fds.size(), -1) == -1)
			throw_error("Poll has failed!");

		for (size_t i = 0; i < poll_fds.size(); i++)
		{
			if (poll_fds[i].revents & POLLIN)
			{
				if (poll_fds[i].fd == server_fd)
					accept_connection();
				else
					recieved_data(poll_fds[i].fd);
			}
		}

	}
}

void Server::init()
{
	createServerSocket();
	std::cout << "Server has been created!" << std::endl;
	launchServer();
}
