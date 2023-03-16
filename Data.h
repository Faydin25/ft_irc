
#ifndef FT_IRC_DATA_H
#define FT_IRC_DATA_H

#include <iostream>
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

#endif //FT_IRC_DATA_H
