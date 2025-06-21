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
		sendResponse("Channel doesn't exist!", fd);
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
			sendResponse("You are not a admin to kick someone!", fd);
			return ;
		}

		Client *client = getClientByNick(nick);
		
		if (!client || !channel->checkClientExist(fd))
		{
			response = nick + " is not a member of " + token;
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
		sendResponse("Channel doesn't exist!", fd);
	}

	return ;
}


