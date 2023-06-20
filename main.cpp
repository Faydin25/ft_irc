#include "Server.hpp"
#include "Client.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    
    Server server(std::stoi(argv[1]), argv[2]);
    
    while (true) {
        // Wait for events on multiple file descriptors
        if (poll(server.users.data(), server.users.size(), -1) == -1) {
            std::cerr << "Failed to poll for events" << std::endl;
            return 1;
        }
        // Process events
        for (size_t i = 0; i < server.users.size(); ++i) {
            if (server.users[i].revents & POLLIN) { //revents: event yok, input event
                // Listening socket has an incoming connection
                if (server.users[i].fd == server.getSocketFd()) {
                    struct sockaddr_in clientAddress;
                    socklen_t clientAddressLength = sizeof(clientAddress);
                    struct pollfd clientSocket;
                    clientSocket.fd = accept(server.getSocketFd(), (struct sockaddr*)&clientAddress, &clientAddressLength);
                    if (clientSocket.fd == -1) {
                        std::cerr << "Failed to accept client connection" << std::endl;
                        continue; //-1 ise sıçıyoruz
                    }
                    clientSocket.events = POLLIN;                                                  
                    server.users.push_back(clientSocket);

                    std::cout << "Accepted client connection" << std::endl;
                }
                // Client socket has incoming data
                else { //çok kritik                             //hmmm bi dk bunu analizlemem lazım..  //buffer ve bytesread i server a taşısak nasıl olurdu acaba. bi deniyom // LAAANN TERMİNALİ KULLANAMIYOMMMMMMM :D
                    char buffer [1024];
                    ssize_t bytesRead = recv(server.users[i].fd, buffer, sizeof(buffer), 0);
                    send(server.users[i].fd, "now you can talk.\n", 18, 0); //example
                    if (bytesRead == -1) {
                        std::cerr << "Failed to receive data from client" << std::endl;
                        continue;
                    }
                    if (bytesRead == 0) {
                        std::cout << "Client disconnected" << std::endl;
                        close(server.users[i].fd);
                        server.users.erase(server.users.begin() + i);
                        --i;
                        continue;
                    }
                    std::cout << "MSG:   " << buffer << std::flush;
                    }
                }
           }
        }
    return (0);
}