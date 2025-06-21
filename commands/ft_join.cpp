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
		if (channel->checkClientExist(fd))
		{
			sendResponse("You are already a member of this channel!", fd);
			return ;
		}
		if (channel->getInviteOnly())
		{
			if (!channel->checkIfInvite(fd))
			{
				sendResponse("You are not invited! sorry buddy!", fd);
				return ;
			}
		}
		if (channel->getPassBoolean())
		{
			iss >> token;
			if (channel->checkPasswordChannel(token))
			{
				sendResponse("You are not invited! sorry buddy!", fd);
				return ;
			}
		}
		channel->addNewMember(fd);
		sendfillmessage(CMD_JOIN, channel->getChannelName(), fd);
		sendfillmessage(RPL_NAMREPLY, channel->getChannelName(), fd);
		sendfillmessage(RPL_ENDOFNAMES, channel->getChannelName(), fd);
		return;
	}
	Channel channel(token, fd, &clients_vector);
	channels_vector.push_back(channel);
	Client *client = getClientByFd(fd);
	std::cout << client->getUserName();
	sendfillmessage(CMD_JOIN, channel.getChannelName(), fd);
	sendfillmessage(RPL_NAMREPLY, channel.getChannelName(), fd);
	sendfillmessage(RPL_ENDOFNAMES, channel.getChannelName(), fd);
	return;
}