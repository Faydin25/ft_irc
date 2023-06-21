#include "Server.hpp"
#include "Client.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    Server server(std::stoi(argv[1]), argv[2]);
    while (true) {
        if (poll(server.users.data(), server.users.size(), -1) == -1) {     // Wait for events on multiple file descriptors
            std::cerr << "Failed to poll for events" << std::endl;
            return 1;
        }
                                                                            // Process events
        for (size_t i = 0; i < server.users.size(); ++i) {
            if (server.users[i].revents & POLLIN){
                if (server.users[i].fd == server.getSocketFd())             // Listening socket has an incoming connection
                        server.incomingConnection(&server);
                else                                                        // Client socket has incoming data
                    if (server.incomingMessage(&server,i) == 0)
                        server.clientDisconnect(&server, i--);
                }
            }
        }
    return (0);
}