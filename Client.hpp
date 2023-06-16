#ifndef CLIENT_HPP
#define CLIENT_HPP

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
#include <list>
#include <vector>
#include <deque>

#include "Server.hpp"

class Client : public Server
{
    public:
        Client();
        ~Client();
        std::string nickname;
        std::string currentChannel;
        std::string username;
        void joinChannelIdentity(std::string str);
        int passwdcontrol;
        int index;
        int isOperator;
        int clientSocketfd;
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength;
};

#endif