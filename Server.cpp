#include "Data.h"

Server::Server(int sockfd, int port, std::string password) {
    //Set Server Address
    struct sockaddr_in server_address, client_address;
    this->port = (uint32_t)port;
    this->sockFd = (uint32_t)sockfd;
    this->password = password;

    //Bind Server Socket
    if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        perror("Bind Failed");
        exit (EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;//AF_INET APv4.
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    //Listen for incoming connections
    if (listen(sockfd, MAX_CLIENTS) < 0)
    {
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "port: " << this->port << std::endl;
    std::cout << "sockFd: " << this->sockFd << std::endl;
    std::cout << "password: " << this->password << std::endl;
}

Server::~Server() {};

uint32_t Server::getServerFD()
{
    return this->sockFd;
}