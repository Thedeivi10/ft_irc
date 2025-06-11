#include "Server.hpp"
#include <iostream>
#include <cstdlib>   // for atoi
#include <csignal>   // for signal handling

int ft_check_args(int ac, char **av)
{
    (void)ac;
    std::string port(av[1]);
    std::string password(av[2]);
    if (port.empty() || port.find_first_not_of("0123456789") != std::string::npos)
        return (std::cerr << "Invalid port number." << std::endl, 1);
    int port_num = atoi(port.c_str()); // removed std::
    if (port_num < 1024 || port_num > 65535)
        return (std::cerr << "Port number must be between 1024 and 65535." << std::endl, 1);
    if (password.empty())
        return (std::cerr << "Password cannot be empty." << std::endl, 1);
    for (unsigned int i = 0; i < password.length(); ++i)
    {
        if (!std::isalnum(password[i]))
            return (std::cerr << "Password must be alphanumeric." << std::endl, 1);
    }
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << "Usage: " << av[0] << " <port> <password>" << std::endl;
        return 1;
    }

    if (ft_check_args(ac, av))
        return 1;

    Server server(av[1], av[2]);
    try
    {
        signal(SIGINT, Server::signal_handler);
        signal(SIGQUIT, Server::signal_handler);
        server.init();
    }
    catch (...)
    {
        return 1;
    }
    return 0;
}
