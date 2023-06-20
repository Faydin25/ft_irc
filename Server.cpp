#include "Server.hpp"

Server::Server()
{}

Server::~Server()
{
    close(this->socketFd);
}

std::string Server::split(const std::string &str, const std::string &delimiters) {
    std::vector<std::string> tokens;
    std::string::size_type last_pos = 0;

    // Find first delimiter
    std::string::size_type pos = str.find_first_of(delimiters, last_pos);

    while (pos != std::string::npos) {
        // Found a token, add it to the vector
        tokens.push_back(str.substr(last_pos, pos - last_pos));

        // Find next delimiter
        last_pos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, last_pos);
    }

    if (last_pos != std::string::npos) {
        tokens.push_back(str.substr(last_pos));
    }

    return tokens.front();
}

int Server::ParsCmd_nextParameter(std::string input)
{
    int i = 0;
    int len = strlen(input.c_str());
    while(input[i] != ' ' && input[i] != '\0')
    {
        if (input[i] == '\0')
            return(1);
        else {
            this->cmd = this->split(input, " ");
            if (input[i] != '\0')
                this->nextParameter = input.substr(i + 1, len);
        }
    }
    return (0);
}

Server::Server(int port, char *paswd)
{
    this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketFd == -1)
        std::cerr << "Failed to create socket" << std::endl;
    this->listeningSocket.fd = this->getSocketFd();
    this->listeningSocket.events = POLLIN;
    this->users.push_back(listeningSocket);
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

std::vector<struct pollfd> Server::getUsers()
{
    return users;
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