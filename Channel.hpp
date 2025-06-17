#pragma once

#include "Server.hpp"

class Channel
{
	private:
		std::vector <int> clients_fds;
		std::string channelName;

	public:
		Channel(std::string channelName);
		~Channel();



		void setChannelName(std::string channelName);
		std::string getChannelName();

};
