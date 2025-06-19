#include "Server.hpp"


std::string Server::fillmessage(int mesage_type, std::string channelName, int fd)
{
	Client *client = getClientByFd(fd);

	if (!client)
        return "";

	Channel *channel = NULL;
	if (channelName != "")
	{
		channel = getChannel(channelName);
		if (!channel)
			return "";
	}
	std::string joinMsg = "";

	switch (mesage_type)
	{
		case (JOIN_START):
			joinMsg = ":" + client->getNickName() +"!" + client->getUserName() + "@localhost JOIN #" + channel->getChannelName() +  "\r\n";
			break;
		case (JOIN_353):
			joinMsg = ":" + this->name + " 353 " + client->getNickName() + " = #" + channel->getChannelName() + " :@" + client->getNickName() + "\r\n";
			break;
		case (JOIN_366):
			joinMsg = ":" + this->name + " 366 " + client->getNickName() + " = #" + channel->getChannelName() + " :End of NAMES list" + "\r\n";
			break;
		default:
			break;
	}
	return joinMsg;
}




