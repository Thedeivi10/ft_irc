#include "../Server.hpp"

void Server::addModeArgument(std::string &token, std::vector<std::pair<std::string, std::string> > &mode_options, std::istringstream &iss)
{
	size_t i = 0;

	while (!token.empty() && i < mode_options.size())
	{
		if (mode_options[i].first == "-i" || mode_options[i].first == "+i" || mode_options[i].first == "-k"
			|| mode_options[i].first == "-l" || mode_options[i].first == "-t" || mode_options[i].first == "+t")
		{
			i++;
			continue ;
		}
		else
		{
			mode_options[i].second = token;
			i++;
		}
		if (!(iss >> token))
			break ;
	}
}

void Server::executeMode(std::vector<std::pair<std::string, std::string> > &mode_options, std::string channelName, int fd)
{
	for (size_t i = 0; i < mode_options.size(); i++)
	{
		std::string first = mode_options[i].first;
		std::string second = mode_options[i].second;
		if (first == "+o" || first == "-o")
			oMode(first, second, channelName, fd);
		else if (first == "+i" || first == "-i")
			iMode(first, channelName, fd);
		else if (first == "+k" || first == "-k")
			kMode(first, second, channelName, fd);
		else if (first == "+l" || first == "-l")
			lMode(first, second, channelName, fd);
		else if (first == "+t" || first == "-t")
			tMode(first, channelName, fd);
	}
}

void Server::oMode(std::string mode, std::string arg, std::string channelName, int fd)
{
	std::string res;
	(void)channelName;

	if (mode == "+o")
	{
		res = mode + " " + arg;
		sendResponse(res, fd);
	}
	else
	{
		res = mode + " " + arg;
		sendResponse(res, fd);
	}
}

void Server::iMode(std::string mode, std::string channelName, int fd)
{
	std::string res;
	(void)channelName;

	if (mode == "+i")
	{
		res = mode;
		sendResponse(res, fd);
	}
	else
	{
		res = mode;
		sendResponse(res, fd);
	}
}

void Server::kMode(std::string mode, std::string arg, std::string channelName, int fd)
{
	std::string res;
	(void)channelName;

	if (mode == "+k")
	{
		res = mode + " " + arg;
		sendResponse(res, fd);
	}
	else
	{
		res = mode + " " + arg;
		sendResponse(res, fd);
	}
}

void Server::lMode(std::string mode, std::string arg, std::string channelName, int fd)
{
	std::string res;
	(void)channelName;

	if (mode == "+l")
	{
		res = mode + " " + arg;
		sendResponse(res, fd);
	}
	else
	{
		res = mode;
		sendResponse(res, fd);
	}
}

void Server::tMode(std::string mode, std::string channelName, int fd)
{
	std::string res;
	(void)channelName;

	if (mode == "+t")
	{
		res = mode;
		sendResponse(res, fd);
	}
	else
	{
		res = mode;
		sendResponse(res, fd);
	}
}

void Server::ft_mode(std::string buffer, int fd)
{
	std::istringstream iss(buffer);
	std::string channelName;
	std::vector<std::pair<std::string, std::string> > mode_options;
	std::string token;

	iss >> channelName;


	if (channelName[0] == '#')
		channelName.erase(0, 1);
	else
	{
		sendResponse("Channel not encounter!", fd);
		return ;
	}
	if (Channel_already_created(channelName))
	{
		if (!checkModeOptions(token, iss, mode_options, fd))
		{
			sendResponse("mode option not encounter!", fd);
			return ;
		}
		addModeArgument(token, mode_options, iss);
		executeMode(mode_options, channelName, fd);
	}
	else
		sendResponse("Channel not encounter!", fd);

	return ;
}

bool Server::checkModeOptions(std::string &token, std::istringstream &iss, std::vector<std::pair<std::string, std::string> > &mode_options, int fd)
{
	std::string mode;
	std::string sign;
	
	iss >> token;
	if (token[0] != '+' && token[0] != '-')
	{
		return false;
	}
	while (!token.empty() && (token[0] == '+' || token[0] == '-'))
	{
		sign = token[0];
		for (size_t i = 1; i < token.size(); i++)
		{
			if (token[i] != 'o' && token[i] != 'i' && token[i] != 'k' &&  token[i] != 'l' && token[i] != 't')
			{
				sendResponse("INVALID MODE!", fd);
			}
			else
			{
				mode = sign + token[i];
				mode_options.push_back(std::make_pair(mode, ""));
			}
		}
		if (!(iss >> token))
		{
			token.clear();
			break ;
		}
	}
	return true;

}
