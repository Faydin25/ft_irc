#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <poll.h>
#include <vector>
#include <unistd.h>

void parser(char *buffer)
{
    char *token = strtok(buffer, " ");
    while (token != NULL)
    {
        std::cout << token << std::endl;
        token = strtok(NULL, " ");
    }
}

int main()
{
    int sockfd;

    /*###################### SOCKET CREATION ######################*/


    //can use try except
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cerr << "Failed to create socket" << std::endl;
        return (1);
    }

    std::cout << "Socket created" << std::endl;
    
    /*############################################################*/

    /*######################## BINDING SOCKET ######################*/

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //bind to any available
    serverAddress.sin_port = htons(4241);  /* <<<<<------------------- BURDA */
    try{
        if (bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        {
            std::cerr << "Failed to bind socket" << std::endl;
            return (1);
        }
    }
    catch(const std::exception& e){ //farklı bir port girilmeli
        std::cerr << e.what() << '\n';
    }
    /*##########################################################*/

    
    /*######################## LISTENING SOCKET ######################*/

    if (listen(sockfd, 5) == -1)
    {
        std::cerr << "Failed to listen socket" << std::endl;
        return (1);
    }

    std::cout << "Socket listening" << std::endl;
    /*##########################################################*/

    
    /*######################## ACCEPTING SOCKET ######################*/
    std::vector<struct pollfd> fds;
    struct pollfd listeningSocket;
    listeningSocket.fd = sockfd;
    listeningSocket.events = POLLIN; // Wait for incoming data
    fds.push_back(listeningSocket);

    // Main event loop
    while (true) {
        // Wait for events on multiple file descriptors
        if (poll(fds.data(), fds.size(), -1) == -1) {
            std::cerr << "Failed to poll for events" << std::endl;
            return 1; // Error handling
        }

        // Process events
        for (size_t i = 0; i < fds.size(); ++i) {
    
           
            if (fds[i].revents & POLLIN) { //revents: event yok, input event
                // Listening socket has an incoming connection
                if (fds[i].fd == sockfd) {
                    std::cout << "sock: "<< sockfd << "client:" << fds[i].fd << std::endl;
                    struct sockaddr_in clientAddress;
                    socklen_t clientAddressLength = sizeof(clientAddress);
                    int clientSockfd = accept(sockfd, (struct sockaddr*)&clientAddress, &clientAddressLength);
                    if (clientSockfd == -1) {
                        std::cerr << "AAAled to accept client connection" << std::endl;
                        continue; // Continue with the next event
                    }

                    // Add the new client socket to the pollfd structure
                    struct pollfd clientSocket;
                    clientSocket.fd = clientSockfd;
                    clientSocket.events = POLLIN; // Wait for incoming data
                    fds.push_back(clientSocket);

                    std::cout << "Accepted client connection" << std::endl;
                }
                // Client socket has incoming data
                else {
                    std::cout << "sock: "<< sockfd << "client:" << fds[i].fd << std::endl;
                    char buffer [1024];
                    ssize_t bytesRead = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                    if (fds[i].fd == 5 && (strcmp(buffer, "/channel4 hello world\n") == 0))
                    {
                        //parser(buffer) => ilk kelime hariç her şey >> user3 (send)
                        //vector<userclass> = user1, user2, user3
                        //user3.index
                        //send(fds[user3.index].fd, parse edilmiş metin)
                        send(fds[i].fd, "hangi user ile konuşmak istiyorsun: \n", 37, 0);
                    } //sadece şurası
                    if (bytesRead == -1) {
                        std::cerr << "Failed to receive data from client" << std::endl;
                        continue; // Continue with the next event
                    }
                    if (bytesRead == 0) {
                        std::cout << "Client disconnected" << std::endl;
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        --i;
                        continue; // Continue with the next event
                        }
                    parser(buffer);
                    }
                }
           } 
        }
    // Close the client socket
    close(sockfd);
    return (0);
}