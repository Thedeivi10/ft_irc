#include "../Server.hpp"

void Server::ft_kick(std::string buffer, int fd)
{	
	std::istringstream iss(buffer);
	std::string token;
	std::string response;

	iss >> token;
	if (token[0] == '#')
		token.erase(0, 1);
	else
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
        return;
	}
	std::string nick;
	iss >> nick;

	if (Channel_already_created(token))
	{
		Channel *channel = getChannel(token);

		if (!channel)
			return ;
		if (!channel->checkIfAdmin(fd))
		{
			sendfillmessage(ERR_CHANOPRIVSNEEDED, channel->getChannelName(), fd);
            return ;
		}

		Client *client = getClientByNick(nick);
		if (!client)
			return ;
		if (!channel->checkClientExist(client->getClifd()))
		{
			std::string requester = getClientByFd(fd)->getNickName();
            response = ":" + this->name + " 441 " + requester + " " + nick + " #" + channel->getChannelName() + " :They aren't on that channel\r\n";
            sendResponse(response, fd);
            return ;
		}
		channel->eraseClientChannel(client->getClifd());
		if (channel->getClients_pairs().size() <= 0)
		{
			response = "Channel: " + channel->getChannelName() + " has been deleted!";
			sendResponse(response, fd);	
			removeChannel(token);
			return ;
		}
		
	}
	else
	{
		sendfillmessage(ERR_NOSUCHCHANNEL, token, fd);
	}

	return ;
}


