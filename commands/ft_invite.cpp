#include "../Server.hpp"

void Server::ft_invite(std::string buffer, int fd)
{
	buffer += " (inviting)";
	sendResponse(buffer, fd);
	return ;
}