#include "../Server.hpp"

void Server::ft_privmsg(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string token;
	std::string destination;
	std::string response;

	iss >> token;

	if (token[0] == '#')
	{
		token.erase(0 ,1);
		destination = token;
		Channel *channel = getChannel(destination);

		if (!channel)
		{
			response = "Channel: " + destination + " doesn't exist!"; 
			sendResponse(response, fd);
		}
		if (!channel->checkClientExist(fd))
		{
			sendResponse("You are not a member of this channel to send a message!", fd);
			return ;
		}
		buffer.erase(0, token.size() + 1);
		response = generateResponse(trimLeading(buffer));
		channelSendResponse(destination, response, fd);
	}
	else
	{
		destination = token;
		Client *client = getClientByNick(destination);

		if (!client)
		{
			response = destination + " doesn't exist!";
			sendResponse(response, fd);
			return ;
		}
		response = buffer.erase(0, token.size());
		sendResponse(response, client->getClifd());
	
	}

	return ;
}

std::string Server::generateResponse(std::string message)
{
	std::string response;

	if (message[0] != ':')
	{
		std::istringstream iss(message);

		iss >> response;
	}
	else
	{
		response = message.erase(0, 1);
	}
	return response;
}