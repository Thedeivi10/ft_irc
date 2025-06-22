#include "../Server.hpp"

void Server::ft_invite(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;

	iss >> token;
	Client *client = getClientByNick(token);
	if (!client)
	{
		std::string response = "Nick: " + token + " doesn't exist!";
		sendResponse(response, fd);
		return ;
	}
	iss >> token;
	if (token[0] != '#')
	{
		std::string response = "Channel: " + token + " doesn't exist!";
		sendResponse(response, fd);
		return ;
	}
	token.erase(0, 1);
	Channel *channel = getChannel(token);
	if (!channel)
	{
		std::string response = "Channel: " + token + " doesn't exist!";
		sendResponse(response, fd);
		return ;
	}
	channel->inviteMember(client->getClifd());
	std::string response = "Nick: " + client->getNickName() + " has been to the channel: " + token;
	sendResponse(response, fd);
	return ;
}