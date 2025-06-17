#include "Channel.hpp"

Channel::Channel(std::string channelName)
{
	this->channelName = channelName;
	clients_fds.clear();
}

Channel::~Channel()
{}

std::string Channel::getChannelName()
{
	return this->channelName;
}

void Channel::setChannelName(std::string channelName)
{
	this->channelName = channelName;
}