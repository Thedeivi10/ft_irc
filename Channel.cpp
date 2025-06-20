#include "Channel.hpp"
#include "irc_messages.hpp"
#include "Server.hpp"

Channel::Channel(std::string channelName, int fd)
{
	this->channelName = channelName;
	clients_pairs.clear();
	this->clients_pairs.push_back(std::make_pair(fd, true));
	this->topic = "";
}

void Channel::addNewMember(int fd)
{
	Server server;
	this->clients_pairs.push_back(std::make_pair(fd, false));
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

bool Channel::checkClientExist(int fd)
{
	if (!clients_pairs.empty())
		return false;
	for (size_t i = 0; i < clients_pairs.size(); i++) 
	{
        if (clients_pairs[i].first == fd)
			return true;
    }
    return false;
}

void Channel::eraseClientChannel(int fd)
{
    std::vector<std::pair<int, bool> >::iterator it;
    
    if (clients_pairs.empty()) {
        return;
    }
    for (it = clients_pairs.begin(); it != clients_pairs.end(); ) {
        if (it->first == fd) {
            it = clients_pairs.erase(it);
        } else {
            ++it;
        }
    }
}

bool Channel::checkIfAdmin(int fd)
{
	for (size_t i = 0; i < clients_pairs.size(); i++) 
	{
        if (clients_pairs[i].first == fd)
		{
			if (clients_pairs[i].second == true)
				return true;
			else
				return false;
		}
    }
    return false;
}

std::vector<std::pair<int, bool> > &Channel::getClients_pairs()
{
	return clients_pairs;
}

