#include "../Server.hpp"

void Server::ft_privmsg(std::string buffer, int fd)
{
	buffer += " (privmsging)";
	sendResponse(buffer, fd);
	return ;
}