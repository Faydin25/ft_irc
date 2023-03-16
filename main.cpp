#include "Data.h"

void	ft_error(std::string str)
{
	std::cout << str << std::endl;
}

void ft_routine(std::string _port, std::string _password)
{
	Data data;
	int sockfd;
	int	new_socket;//Now we can hear!
	data.port = std::stoi(_port);
	data.password = _password;

	struct sockaddr_in serv_addr, cli_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == 0)
	{
		perror("Socket Creation Failed");
		exit(EXIT_FAILURE);
	}
	//Set Server Address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(8080);

	//Bind Server Socket
	if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Bind Failed");
		exit (EXIT_FAILURE);
	}

	//Listen for imcoming connections
	if (listen(sockfd, 5) < 0)
	{
		perror("Listen Failed");
		exit(EXIT_FAILURE);
	}
	while(1) {
		int addrlen = sizeof(cli_addr);
		new_socket = accept(sockfd, (struct sockaddr*)&cli_addr, (socklen_t*)&addrlen);
	}

}

int main(int ac, char *av[])
{
	if (ac == 3)
		ft_routine(av[1], av[2]);
	else
		ft_error("Usage Error: ./irc <port> password");
	return 0;
}