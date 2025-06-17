#include "../Server.hpp"

void Server::ft_kick(std::string buffer, int fd)
{	
	buffer += " (kicking @$$)";
	sendResponse(buffer, fd);
	return ;
}