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

class Client;

class Server
{
    public:
        int socketFd;
        std::string paswd;
        int socketPort;
        const char* hostName;
        unsigned int userCount;
        std::vector<struct pollfd> users;
        std::vector<class Client> clients; //-binam  denemek icin ekledim, ve galiba oldu
        //std::map<struct pollfd, class Client> userMap;
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
    int clientDisconnect(Server *server, int i);
    int incomingConnection(Server *server);
    int incomingMessage(Server *server, int i);
    Client whenUserFirstJoin(Server *server, int fd);
};

#endif