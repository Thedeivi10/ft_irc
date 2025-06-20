#pragma once


enum COMMAND {
    CMD_JOIN,        // :<nick>!<user>@<host> JOIN #channel
    CMD_PASS,        // (no direct response, used only for internal password validation)
    CMD_NICK,        // :<old_nick>!<user>@<host> NICK :<new_nick>
    CMD_USER,        // (no direct response, triggers sending numerics 001-005)
    CMD_PING,        // PING :<token>
    CMD_PONG,        // PONG :<token>
    CMD_QUIT,        // :<nick>!<user>@<host> QUIT :<quit message>
    CMD_PRIVMSG,     // :<nick>!<user>@<host> PRIVMSG <target> :<message>
    CMD_NOTICE,      // :<nick>!<user>@<host> NOTICE <target> :<message>
    CMD_PART,        // :<nick>!<user>@<host> PART #channel [:part message]
    CMD_MODE,        // :<nick>!<user>@<host> MODE #channel +mode [params]
    CMD_TOPIC,       // :<nick>!<user>@<host> TOPIC #channel :<new topic>
    CMD_INVITE,      // :<nick>!<user>@<host> INVITE <otherNick> :#channel
    CMD_LIST,        // (client sends LIST; you respond with 322/323)
    CMD_KICK,        // :<nick>!<user>@<host> KICK #channel <nick> :<reason>
    CMD_KILL         // :<op>!<user>@<host> KILL <target> :<reason>
};


enum RPL {
    // ─────────── REGISTRATION / CONNECTION ───────────
    RPL_WELCOME = 001,         // :<server> 001 <nick> :Welcome to IRC
    RPL_YOURHOST = 002,        // :<server> 002 <nick> :Your host is ...
    RPL_CREATED = 003,         // :<server> 003 <nick> :This server was created ...
    RPL_MYINFO = 004,          // :<server> 004 <nick> <server> <version> <user_modes> <chan_modes>
    RPL_ISUPPORT = 005,        // :<server> 005 <nick> PREFIX=(ov)@+ CHANTYPES=# ...

    ERR_ALREADYREGISTERED = 462,   // :<server> 462 <nick> :You may not reregister
    ERR_PASSWDMISMATCH = 464,      // :<server> 464 <nick> :Password incorrect
    ERR_ERRONEUSNICKNAME = 432,    // :<server> 432 * <nick> :Erroneous nickname
    ERR_NICKNAMEINUSE = 433,       // :<server> 433 * <nick> :Nickname is already in use
    ERR_NEEDMOREPARAMS = 461,      // :<server> 461 <nick> <command> :Not enough parameters

    // ─────────── CHANNEL MANAGEMENT ───────────
    RPL_CHANNELMODEIS = 324,   // :<server> 324 <nick> #channel +modes
    RPL_CREATIONTIME = 329,    // :<server> 329 <nick> #channel <timestamp>
    RPL_NOTOPIC = 331,         // :<server> 331 <nick> #channel :No topic is set
    RPL_TOPIC = 332,           // :<server> 332 <nick> #channel :<topic>
    RPL_TOPICWHOTIME = 333,    // :<server> 333 <nick> #channel <nick> <timestamp>
    RPL_NAMREPLY = 353,        // :<server> 353 <nick> = #channel :@nick1 nick2
    RPL_ENDOFNAMES = 366,      // :<server> 366 <nick> #channel :End of NAMES list
    RPL_INVITING = 341,        // :<server> 341 <nick> <target> #channel

    ERR_NOSUCHCHANNEL = 403,     // :<server> 403 <nick> #channel :No such channel
    ERR_CANNOTSENDTOCHAN = 404,  // :<server> 404 <nick> #channel :Cannot send to channel
    ERR_USERNOTINCHANNEL = 441,  // :<server> 441 <nick> <target> #channel :They aren't on that channel
    ERR_NOTONCHANNEL = 442,      // :<server> 442 <nick> #channel :You're not on that channel
    ERR_USERONCHANNEL = 443,     // :<server> 443 <nick> <target> #channel :is already on channel
    ERR_CHANOPRIVSNEEDED = 482,  // :<server> 482 <nick> #channel :You're not channel operator
    ERR_INVITEONLYCHAN = 473,    // :<server> 473 <nick> #channel :Cannot join channel (+i)
    ERR_BADCHANNELKEY = 475,     // :<server> 475 <nick> #channel :Cannot join channel (+k)
    ERR_CHANNELISFULL = 471,     // :<server> 471 <nick> #channel :Cannot join channel (+l)
    ERR_UNKNOWNMODE = 472,       // :<server> 472 <nick> <char> :is unknown mode char to me
    ERR_KEYSET = 467,            // :<server> 467 <nick> #channel :Channel key already set
    ERR_INVALIDMODEPARAM = 696,  // :<server> 696 <nick> #channel <char> :Invalid mode parameter

    // ─────────── MESSAGING ───────────
    ERR_NOSUCHNICK = 401,        // :<server> 401 <nick> <target> :No such nick/channel
    ERR_NOTEXTTOSEND = 412,      // :<server> 412 <nick> :No text to send

    // ─────────── WHO / LIST SUPPORT ───────────
    RPL_WHOREPLY = 352,          // :<server> 352 <nick> #channel user host server nick H :0 realname
    RPL_ENDOFWHO = 315,          // :<server> 315 <nick> #channel :End of WHO list
    RPL_LIST = 322,              // :<server> 322 <nick> #channel users :topic
    RPL_LISTEND = 323            // :<server> 323 <nick> :End of LIST
};
