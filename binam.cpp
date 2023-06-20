#include "Server.hpp"
#include "Client.hpp"

ssize_t getUserInfo(int fd, char *buffer, class Client users)
{
    send(fd, "\nPasswd: ", 9, 0);
    ssize_t bytesRead = recv(fd, buffer, sizeof(buffer), 0);
    users.joinServerIdentity(buffer);
    send(fd, "\n Name: ", 9, 0);
    bytesRead += recv(fd, buffer, sizeof(buffer), 0);
    users.joinServerIdentity(buffer);
     send(fd, "\n nickname: ", 13, 0);
    bytesRead += recv(fd, buffer, sizeof(buffer), 0);
    users.joinServerIdentity(buffer); //burda da clientin adresinden fonksiyonlarına ulasıp icini doldurtuyodum . cpp degil de c gibi yazdım daha cok
                                                //bişey dicem  .yes.mai n'e babksana düzenledim baya, onu içine implement etmeyi denesene bi kopyasını oluştuurp. tammadır kral < 3 <3<3<33<3<3
    return (bytesRead);
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    
    Server server(std::stoi(argv[1]), argv[2]);

    
    std::vector<struct pollfd> fds;
    std::vector<class Client> users; //clientler burda tutulcaktı
    char buffer[1024];
    ssize_t bytesRead;
    struct pollfd listeningSocket;
    listeningSocket.fd = server.getSocketFd();
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
            send(fds[0].fd, "Password: ", 10, 0);
            if (fds[i].revents & POLLIN) { //revents: event yok, input event
                // Listening socket has an incoming connection
                if (fds[i].fd == server.getSocketFd()) {
                    struct sockaddr_in clientAddress;
                    socklen_t clientAddressLength = sizeof(clientAddress);
                    int clientSockfd = accept(server.getSocketFd(), (struct sockaddr*)&clientAddress, &clientAddressLength);
                    if (clientSockfd == -1) {
                        std::cerr << "Failed to accept client connection" << std::endl;
                        continue; // Continue with the next event
                    }

                    // Add the new client socket to the pollfd structure
                    struct pollfd clientSocket;
                    clientSocket.fd = clientSockfd;
                    clientSocket.events = POLLIN; // Wait for incoming data
                    fds.push_back(clientSocket);
                    users.push_back(Client(clientSocket.fd)); // burda clienti olusturup sadece obje olarak saklamayı düsündüm
                    std::cout << "Accepted client connection" << std::endl;
                    
                }
                // Client socket has incoming data
                else {
                    
                    send(fds[i].fd, "Welcome IRC Take one pass, name and nickname\n", 46, 0);
                    bytesRead = getUserInfo(fds[i].fd, buffer, users[i - 1]); //mevzu şu fonksiyondu da . bu tarz çalışma mantığı cpp ye aykırı olabilir

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
                    //std::cout << "MSG:   " << buffer << std::flush;//flush ne amk ya, bi sike yaramıo? -yigit , sifonu çek diyo sana xd -berkay
                    }
                }
           }
        }
    return (0);
}