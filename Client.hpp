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

        std::map<std::string, std::vector<Client> > _channels;//First->Channels Second->Users
        int             passwdcontrol;//
        int             clientSockfd;//
        std::string     nickname;//
        std::string     username;//
        int             client_id;
        int             isOperator;
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength;

        std::map<std::string, std::vector<Client> > getChannels();
        std::vector<Client> getChannelUsers(std::string channelName);
        void sendMessageToChannel(Client user, std::string channelName);
        int joinServerIdentity(std::string str);
        void createChannel(std::string channel_name, Client &user);
        void Client::cmdKick(Client user, std::string cmd, std::string NextParameter);
        void FindCommands(Client user, std::string cmd, std::string NextParameter);
        void cmdPrivmsg( Client user, std::string cmd, std::string NextParameter);
        void cmdNotice( Client user, std::string cmd, std::string NextParameter);
        void cmdJoin( Client user, std::string cmd, std::string NextParameter);
        void cmdQuit( Client user, std::string cmd, std::string NextParameter);
        void cmdPing( Client user, std::string cmd, std::string NextParameter);
};

#endif