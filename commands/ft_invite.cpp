#include "../Server.hpp"

void Server::ft_invite(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;

	iss >> token;
	Client *client = getClientByNick(token);
	if (!client)
	{
		 Client *requester = getClientByFd(fd);
		std::string response = ":" + this->name + " 401 " + (requester ? requester->getNickName() : "*") + " " + token + " :No such nick/channel\r\n";
		sendResponse(response, fd);
		return ;
	}
	iss >> token;
	if (token[0] != '#')
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
		return ;
	}
	token.erase(0, 1);
	Channel *channel = getChannel(token);
	if (!channel)
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
		return ;
	}
	channel->inviteMember(client->getClifd());
	std::string response = "Nick: " + client->getNickName() + " has been invited to the channel: " + token;
	sendResponse(response, fd);
	return ;
}