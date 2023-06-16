#include "Server.hpp"

Server::Server()
{}

Server::~Server()
{
    close(this->socketFd);
}

Server::Server(int port, char *paswd)
{
    this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketFd == -1)
        std::cerr << "Failed to create socket" << std::endl;
    this->hostName = "localhost";
    this->paswd = paswd;
    this->socketPort = port;
    std::cout << "Socket created" << std::endl;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //bind to any available
    serverAddress.sin_port = htons(this->socketPort);
    try{
        if (bind(this->socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
            std::cerr << "Failed to bind socket" << std::endl;
    }
    catch(const std::exception& e){ //farklı bir port girilmeli
        std::cerr << e.what() << '\n';
    }
    if (listen(this->socketFd, this->userCount) == -1) //5 değişecektir
        std::cerr << "Failed to listen socket" << std::endl;

    std::cout << "Socket listening" << std::endl;
}

std::vector<std::string> Server::getUsers()
{
    return _userList;
}

std::map<std::string, std::vector<std::string> > Server::getChannels()
{
    return _channels;
}

std::vector<std::string> Server::getChannelUsers(std::string channelName)
{
    if(this->_channels.find(channelName) != this->_channels.end())
        return this->_channels[channelName];
    else
        return std::vector<std::string>();
}

int Server::checkPasswd(char *paswd)
{
    if(strcmp(this->paswd.c_str(), paswd) == 0)
        return 1;
    else
        return 0;
}

int Server::getSocketFd()
{
    return this->socketFd;
}