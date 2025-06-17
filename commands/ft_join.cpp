#include "../Server.hpp"

void Server::ft_join(std::string buffer, int fd)
{
	buffer += " (joining)";
	sendResponse(buffer, fd);
	if (!buffer.empty() && buffer[0] == '#')
    	buffer.erase(0, 1);
	if (Channel_already_created(buffer))
	{
		//add_to_channel(fd);
		return;
	}
	Channel chanel(buffer);
	return 
	
	
	
	
	
	
	;
}