#pragma once

#include "Server.hpp"

class Client;
class Server;

class Channel
{
	private:
		std::string channelName;
		std::vector<std::pair<int , bool> > clients_pairs;
		std::string topic;
		bool hasTopic;
		
	public:
		Channel(std::string channelName, int fd);
		~Channel();

		void setChannelName(std::string channelName);
		std::string getChannelName();

		void addNewMember(int fd);
		bool checkClientExist(int fd);
		void eraseClientChannel(int fd);
		bool checkIfAdmin(int fd);
		void setTopic(const std::string& topic);
		std::string getTopic() const;
		bool hasTopic() const;


		std::vector<std::pair<int, bool> > getClients_pairs();
};
