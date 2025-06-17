#include "../Server.hpp"

void Server::ft_mode(std::string buffer, int fd)
{
	buffer += " (moding)";
	sendResponse(buffer, fd);
	return ;
}