#include "../Server.hpp"

void Server::ft_list(std::string buffer, int fd)
{
	buffer += " (listing)";
	sendResponse(buffer, fd);
	return ;
}