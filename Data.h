#pragma once

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

#include <iostream>
#include <poll.h>
#include <sys/socket.h> // socket fonksiyonu için gereklidir
#include <netinet/in.h> // sockaddr_in yapısı için gereklidir
#include <unistd.h>     // close fonksiyonu için gereklidir

class Data
{
	public:
		int port;
		std::string password;
	private:
		;
};

class Server
{
    public:
        Server(int sockfd, int port, std::string password);
        ~Server();
        uint32_t getServerFD();
        uint32_t getPort();

    private:
        std::string password;
        uint32_t	sockFd;
        uint32_t	port;
};