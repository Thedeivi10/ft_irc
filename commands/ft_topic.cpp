#include "../Server.hpp"
void Server::ft_topic(const std::string& buffer, int fd) {
    Client* client = getClientByFd(fd);
    Channel* channel = getChannelName();

    if (!channel) {
        sendfillmessage(ERR_NOSUCHCHANNEL, "", fd);
        return;
    }
    std::string newTopic;
    size_t double_dot = buffer.find(":");
    if (double_dot != std::string::npos)
        newTopic = buffer.substr(double_dot + 2);

    if (newTopic.empty()) {
        if (channel->hasTopic()) {
            sendfillmessage(RPL_TOPIC, channel->getChannelName(), fd);
            sendResponse(" :" + channel->getTopic(), fd);
        } else {
            sendfillmessage(RPL_NOTOPIC, channel->getChannelName(), fd);
        }
    } else {
        if (!channel->checkIfAdmin(fd)) {
            sendfillmessage(RPL_NOT_OPERATOR, channel->getChannelName(), fd);
            return;
        }
        channel->setTopic(newTopic);
        sendfillmessage(RPL_TOPICCHANGED, channel->getChannelName(), fd);
    }
}
