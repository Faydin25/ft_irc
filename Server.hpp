#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <poll.h>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <map>

class Server
{
    public:
    int socketFd;
    std::string paswd;
    int socketPort;
    const char* hostName;
    unsigned int userCount;
    std::vector<std::string> _userList;
    std::map<std::string, std::vector<std::string> > _channels;

    Server();
    Server(int port, char *paswd);
    ~Server();
    int getSocketFd();
    unsigned int getUserCount();
    int checkPasswd(char *paswd);
    std::vector<std::string> getUsers();
    std::map<std::string, std::vector<std::string> > getChannels();
    std::vector<std::string> getChannelUsers(std::string channelName);

};

#endif