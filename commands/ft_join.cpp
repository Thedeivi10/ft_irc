#include "../Server.hpp"

void Server::ft_join(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;
	const std::string invalidChars = " ,";

	iss >> token;
	if (!token.empty() && token [0] == '#')
    	token.erase(0, 1);
	else
	{
		sendResponse("Invalid name Channel", fd);
		 return;
	}
	if (token.find_first_of(invalidChars) != std::string::npos || (token.length() > 1 && token.substr(0,2)== "^G")
		|| token.find(' ') != std::string::npos)
	{  
		sendResponse("Invalid character in the channel's name", fd);
		return ;
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
	Client *client = getClientByFd(fd);
	std::cout << client->getUserName();
	std::string joinMsg = ":" + client->getNickName() +"!" + client->getUserName() + "@localhost JOIN #" + channel.getChannelName() +  "\r\n";
	sendResponse(joinMsg, fd);
	std::string namreply = ":" + this->name + " 353 " + client->getNickName() + " = #" + channel.getChannelName() + " :@" + client->getNickName() + "\r\n";
	sendResponse(namreply,fd);
	std::string endofnames = ":" + this->name + " 366 " + client->getNickName() + " = #" + channel.getChannelName() + " :End of NAMES list" + "\r\n";
	sendResponse(endofnames, fd);
	return;
}