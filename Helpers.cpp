#include "Server.hpp"

bool iequals(const std::string &a, const std::string &b) 
{
	if (a.size() != b.size()) 
		return false;
	for (size_t i = 0; i < a.size(); ++i)
	{
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	}
	return true;
}

std::string trimLeading(std::string s) 
{
	size_t pos = s.find_first_not_of(" \t\r\n");
	if (pos != std::string::npos)
		s.erase(0, pos);
	return s;
}

std::string getCommandArg(std::string buffer, const std::string &cmd) 
{
	if (buffer.size() < cmd.size()) 
		return "";
	buffer.erase(0, cmd.size());
	return trimLeading(buffer);
}
