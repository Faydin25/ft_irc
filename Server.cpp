#include "Data.h"

Server::Server(int sockfd, int port, std::string password) {
    //Set Server Address
    struct sockaddr_in server_address, client_address;

    socklen_t client_len = sizeof(client_address);
    server_address.sin_family = AF_INET;//AF_INET APv4.
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(data.port);

    //Bind Server Socket
    if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        perror("Bind Failed");
        exit (EXIT_FAILURE);
    }
}

Server::~Server() {};
