#include "Client.hpp"

Client::Client(int client_fd, const struct sockaddr_in &addr)
    : fd(client_fd), ip(inet_ntoa(addr.sin_addr)), port(ntohs(addr.sin_port)) {}

int Client::get_fd() const 
{
    return fd;
}

std::string Client::get_ip() const 
{
    return ip;
}

int Client::get_port() const 
{
    return port;
}
