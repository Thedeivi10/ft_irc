#include "Server.hpp"
#include "irc_messages.hpp"


void Server::sendfillmessage(int mesage_type, std::string channelName, int fd)
{
	Client *client = getClientByFd(fd);

	if (!client)
        return ;

	Channel *channel = NULL;
	if (channelName != "")
	{
		channel = getChannel(channelName);
		if (!channel)
			return ;
	}
	std::string joinMsg = "";

	switch (mesage_type)
	{
		case (CMD_JOIN):
			joinMsg = ":" + client->getNickName() +"!" + client->getUserName() + "@localhost JOIN #" + channel->getChannelName() +  "\r\n";
			break;
		case (CMD_TOPIC):
			joinMsg = ":" + client->getNickName() +"!" + client->getUserName() + "@localhost TOPIC #" + channel->getChannelName() + NEW TOPIC HERE +  "\r\n";
			break;
		case (RPL_NAMREPLY):
			joinMsg = ":" + this->name + " 353 " + client->getNickName() + " = #" + channel->getChannelName() + " :@" + client->getNickName() + "\r\n";
			break;
		case (RPL_ENDOFNAMES):
			joinMsg = ":" + this->name + " 366 " + client->getNickName() + " #" + channel->getChannelName() + " :End of NAMES list" + "\r\n";
			break;
		case (RPL_NOT_OPERATOR):
			joinMsg = ":" + client->Server() +"482" + client->getNickName() + channelName + channel->getChannelName() + ":You're not channel operator" +  "\r\n";
			break;
		default:
			break;
	}
	sendResponse(joinMsg, fd);
}




