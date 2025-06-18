#include "../Server.hpp"

void Server::ft_join(std::string buffer, int fd)
{
	std::istringstream iss(buffer);

	std::string token;

	iss >> token;
	if (!token.empty() && token [0] == '#')
    	token.erase(0, 1);
	else
	{
		sendResponse("Invalid name Channel", fd);
		 return;
	}
	if (Channel_already_created(token))
	{
		Channel *channel  = getChannel(token);
		channel->addNewMember(fd);
		std::cout << "already created!" << std::endl; 
		return;
	}
	Channel channel(token, fd);
	channels_vector.push_back(channel);
	std::string newchannelname = "New channel: '" + token + "' has been created!";
	sendResponse(newchannelname,fd);
	return;
}