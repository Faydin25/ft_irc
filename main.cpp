#include "Data.h"

void	ft_error(std::string str)
{
	std::cerr << str << std::endl;
}

void ft_routine(std::string _port, std::string _password)
{
	Data data;
	int sockfd;
    int poll_ret;
	int	new_socket;
	data.port = std::stoi(_port);
	data.password = _password;

	int server_socket, client_socket[MAX_CLIENTS], active_clients = 0;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len = sizeof(client_address);
	char buffer[BUFFER_SIZE];

	//Create Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == 0)
	{
		std::perror("Socket Creation Failed");
		exit(EXIT_FAILURE);
	}

    Server server(sockfd, data.port, data.password);

    struct pollfd poll_fds[MAX_CLIENTS + 1];
    poll_fds[0].fd = server.getServerFD();
    poll_fds[0].events = POLLIN;

    while (1)
    {
        poll_ret = poll(poll_fds, active_clients + 1, -1);
        if (poll_ret < 0)
        {
            ft_error("Poll Error!");
            exit(EXIT_FAILURE);
        }
        if (poll_fds[0].revents && POLLIN)
        {
            client_socket[active_clients] = accept(server.getServerFD(), (struct sockaddr *)&client_address, &client_len);
            if (client_socket[active_clients] < 0)
            {
                ft_error("Error Client!");
                exit(EXIT_FAILURE);
            }
        }
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