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
#include <cstring>

class Server
{
    public:
        int socketFd;
        std::string paswd;
        int socketPort;
        const char* hostName;
        unsigned int userCount;
        std::vector<struct pollfd> users;
        struct pollfd listeningSocket;
        std::vector<std::string> TotChannels;
        char buffer [1024];
        std::string cmd;//
        std::string nextParameter;//

    Server();
    Server(int port, char *paswd);
    ~Server();
    int getSocketFd();
    unsigned int getUserCount();
    int checkPasswd(char *paswd);
    std::vector<struct pollfd> getUsers();
    std::string split(const std::string &str, const std::string &delimiters);//
    int ParsCmd_nextParameter(std::string input);//
};

#endif