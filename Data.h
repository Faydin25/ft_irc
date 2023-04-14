#pragma once

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

#include <iostream>
#include <sys/socket.h> // socket fonksiyonu için gereklidir
#include <netinet/in.h> // sockaddr_in yapısı için gereklidir
#include <unistd.h>     // close fonksiyonu için gereklidir

class Data
{
	public:
		int port;
		std::string password;
		void setServerFD(uint32_t fd);//!!
	private:
		uint32_t serverFD;
};

class Server
{
    public:
        Server(int sockfd, int port, std::string password);
        ~Server();
    private:
};