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
		case (RPL_WELCOME):
			joinMsg = ":" + this->name + " 001 " + client->getNickName() + " :Welcome to IRC" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 002 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_CREATED):
			joinMsg = ":" + this->name + " 003 " + client->getNickName() + " :This server was created ..." + "\r\n";
			break;
		case (RPL_MYINFO):
			joinMsg = ":" + this->name + " 004 " + client->getNickName() +
              " " + this->name + " ft_irc-1.0" + " o" + " itkl" + "\r\n";
			break;
		/*
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 315 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 322 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 323 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 324 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 329 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 331 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 332 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 333 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 341 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 352 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_NAMREPLY):
			joinMsg = ":" + this->name + " 353 " + client->getNickName() + " = #" + channel->getChannelName() + " :@" + client->getNickName() + "\r\n";
			break;
		case (RPL_ENDOFNAMES):
			joinMsg = ":" + this->name + " 366 " + client->getNickName() + " #" + channel->getChannelName() + " :End of NAMES list" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 401 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 403 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 404 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 412 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 432 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 433 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 441 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 442 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 443 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 461 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 462 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 467 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 471 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 472 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 473 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 475 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 464 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 482 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		case (RPL_YOURHOST):
			joinMsg = ":" + this->name + " 696 " + client->getNickName() + " :Your host is localhost.irc" + "\r\n";
			break;
		*/
		default:
			break;
	}
	sendResponse(joinMsg, fd);
}




