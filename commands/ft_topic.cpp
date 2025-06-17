#include "../Server.hpp"

void Server::ft_topic(std::string buffer, int fd)
{
	buffer += " (topicing)";
	sendResponse(buffer, fd);
	return ;
}