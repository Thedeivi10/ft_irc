#include "Channel.hpp"

Channel::Channel(std::string channelName, int fd)
{
	this->channelName = channelName;
	clients_pairs.clear();
	this->clients_pairs.push_back(std::make_pair(fd, true));
}

void Channel::addNewMember(int fd)
{
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
	for (size_t i = 0; i < clients_pairs.size(); i++) 
	{
        if (clients_pairs[i].first == fd)
			return true;
    }
    return false;
}

void Channel::eraseClientChannel(int fd)
{
	for (std::vector<std::pair<int, bool> >::iterator it = clients_pairs.begin(); it != clients_pairs.end(); ++it) {
        if (it->first == fd) {
            clients_pairs.erase(it);
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

std::vector<std::pair<int, bool> > Channel::getClients_pairs()
{
	return clients_pairs;
}

