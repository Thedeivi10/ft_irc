#include "../Server.hpp"

void Server::ft_part(std::string buffer, int fd)
{
	buffer += " (parting)";
	sendResponse(buffer, fd);
	return ;
}