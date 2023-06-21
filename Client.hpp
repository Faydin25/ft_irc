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
#include <string.h>

#include "Server.hpp"


class Client : public Server//Server'da benim bir  tane kullanıcıların tutulduğu bir vector almam lazım(referansı ile!)
{
    public:
        Client();
        ~Client();

        int             passwdcontrol;//
        int             clientSockfd;//
        std::string     nickname;//
        std::string     username;//
        int             client_id;
        int             index;
        int             isOperator;
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength;
        std::vector<std::string> myChannels;

        void cmdQuit( Client user, std::string cmd, std::string NextParameter);
        int joinServerIdentity(Client *client, std::string str);
        /*
        void Client::cmdKick(Client user, std::string cmd, std::string NextParameter);
        void FindCommands(Client user, std::string cmd, std::string NextParameter);
        void cmdPrivmsg( Client user, std::string cmd, std::string NextParameter);
        void cmdNotice( Client user, std::string cmd, std::string NextParameter);
        void cmdJoin( Client user, std::string cmd, std::string NextParameter);
      
        void cmdPing( Client user, std::string cmd, std::string NextParameter);*/
};

struct s_global
{
    std::map<std::string, std::vector<Client> > _channels;//First->Channels Second->Users
    std::string topic;
};
extern s_global global;

#endif