#include "Server.hpp"

bool Server::signal_flag = false;

Server::Server(const std::string &port_str, const std::string &password_str) 
{
    this->password = password_str;
    this->port = std::atoi(port_str.c_str());
    this->server_fd = -1;
    this->poll_fds.clear();
}

void Server::signal_handler(int sig) 
{
	(void)sig;
    std::cout << "\nSignal received! Server shutting down..." << std::endl;
    signal_flag = true;
}

void Server::create_server_socket() 
{
    int opt = 1;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        throw std::runtime_error("Failed to create socket");

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("Failed to set socket options");

    if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Failed to set socket to non-blocking mode");

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Failed to bind socket");

    if (listen(server_fd, SOMAXCONN) < 0)
        throw std::runtime_error("Failed to listen on socket");

    struct pollfd server_poll_fd;
    server_poll_fd.fd = server_fd;
    server_poll_fd.events = POLLIN;
    server_poll_fd.revents = 0;
    poll_fds.push_back(server_poll_fd);
}

void Server::accept_connection() 
{
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    if (client_fd < 0) 
	{
        if (errno != EWOULDBLOCK && errno != EAGAIN)
            throw std::runtime_error("Failed to accept connection");
        return;
    }

    if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0) 
	{
        close(client_fd);
        throw std::runtime_error("Failed to set client socket to non-blocking mode");
    }

    struct pollfd new_fd;
    new_fd.fd = client_fd;
    new_fd.events = POLLIN;
    new_fd.revents = 0;
    poll_fds.push_back(new_fd);

	Client client(client_fd, client_addr);
	clients_vector.push_back(client);
    std::cout << "New connection accepted from " << inet_ntoa(client_addr.sin_addr)
              << ":" << ntohs(client_addr.sin_port) << std::endl;
}

void Server::receive_data(int fd) 
{
    char buffer[1024];
    ssize_t bytes_received = recv(fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0)
        throw std::runtime_error("Failed to receive data");
    else if (bytes_received == 0) {
        close(fd);
        std::cout << "Client disconnected." << std::endl;
        return;
    }

    buffer[bytes_received] = '\0';
    std::cout << "Received data: " << buffer << std::endl;
}

void Server::launch() 
{
    while (!signal_flag)
	{
        int ret = poll(&poll_fds[0], poll_fds.size(), -1);
        if (ret < 0) 
		{
            close_fds();
            throw std::runtime_error("Poll failed");
        }

        for (size_t i = 0; i < poll_fds.size(); ++i) 
		{
            if (poll_fds[i].revents & POLLIN) 
			{
                if (poll_fds[i].fd == server_fd)
                    accept_connection();
                else
                    receive_data(poll_fds[i].fd);
            }
        }
    }
    close_fds();
}

void Server::init() 
{
    create_server_socket();
    std::cout << "Server initialized on port " << port << std::endl;
    launch();
}

void Server::close_fds() 
{
    for (size_t i = 0; i < poll_fds.size(); ++i)
	{
        if (poll_fds[i].fd != -1)
            close(poll_fds[i].fd);
    }
    poll_fds.clear();
    if (server_fd != -1)
        close(server_fd);
    server_fd = -1;
}
