#include "Data.h"

void	ft_error(std::string str)
{
	std::cerr << str << std::endl;
}

void ft_routine(std::string _port, std::string _password)
{
	Data data;
	int sockfd;
	int	new_socket;//Now we can hear!
	data.port = std::stoi(_port);
	data.password = _password;


	int server_socket, client_socket[MAX_CLIENTS], active_clients = 0;
	char buffer[BUFFER_SIZE];


	//Create Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == 0)
	{
		std::perror("Socket Creation Failed");
		exit(EXIT_FAILURE);
	}

    Server server(sockfd, data.port, data.password);

//-------------------------------------------------------------------------------------------------
	//Listen for imcoming connections
	if (listen(sockfd, MAX_CLIENTS) < 0)
	{
		perror("Listen Failed");
		exit(EXIT_FAILURE);
	}
}

int main(int ac, char *av[])
{
	if (ac == 3)
		ft_routine(av[1], av[2]);
	else {
        ft_error("Usage Error: ./irc <port> password");
        return 1;
    }
	return 0;
}