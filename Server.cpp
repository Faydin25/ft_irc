#include "Server.hpp"
#include "Client.hpp"

Server::Server()
{
}

Server::~Server()
{
    close(this->socketFd);
}

std::string Server::split(const std::string &str, const std::string &delimiters) {
    std::vector<std::string> tokens;
    std::string::size_type last_pos = 0;

    // Find first delimiter
    std::string::size_type pos = str.find_first_of(delimiters, last_pos);

    while (pos != std::string::npos) {
        // Found a token, add it to the vector
        tokens.push_back(str.substr(last_pos, pos - last_pos));

        // Find next delimiter
        last_pos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, last_pos);
    }

    if (last_pos != std::string::npos) {
        tokens.push_back(str.substr(last_pos));
    }

    return tokens.front();
}

int Server::ParsCmd_nextParameter(std::string input)
{
    int i = 0;
    int len = strlen(input.c_str());
    while(input[i] != ' ' && input[i] != '\0')
    {
        if (input[i] == '\0')
            return(1);
        else {
            this->cmd = this->split(input, " ");
            if (input[i] != '\0')
                this->nextParameter = input.substr(i + 1, len);
        }
    }
    return (0);
}

int Server::incomingMessage(Server *server, int i)
{
        std::string* buffer = new std::string();
        ssize_t bytesRead = recv(server->users[i].fd, static_cast<void*>(&buffer), sizeof(buffer), 0);
        if (bytesRead == -1) {
            std::cerr << "Failed to receive data from client" << std::endl;
        }
        //std::cout << "İncomingMessage():   " << &buffer << std::endl;
        //parsera yönlendir.
    return (bytesRead);
}

Client Server::whenUserFirstJoin(Server *server, int fd)
{
    (void) server;
    Client client;
    char buffer [1024];
    ssize_t bytesRead;

    send(fd, "\npassword : ", 13, 0); 
    bytesRead = recv(fd, buffer, sizeof(buffer), 0);
    client.joinServerIdentity(&client,buffer);

    send(fd, "\nusrname : ", 12, 0);
    bytesRead = recv(fd, buffer, sizeof(buffer), 0);
    client.joinServerIdentity(&client,buffer);

    send(fd, "\nnickname : ", 13, 0);
    bytesRead = recv(fd, buffer, sizeof(buffer), 0);
    client.joinServerIdentity(&client,buffer);

    buffer[0] = 0;
    std::cout << client.username << std::endl;              //CLİENTİN İÇİ OÇUİ
    return (client);
}

int Server::incomingConnection(Server *server)
{
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    struct pollfd clientSocket;
    clientSocket.fd = accept(getSocketFd(), (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket.fd == -1) {
        std::cerr << "Failed to accept client connection" << std::endl;
        //continue; //-1 ise sıçıyoruz //client disconnect e göndeririz. 
    }
    clientSocket.events = POLLIN;                                        
    server->users.push_back(clientSocket);
    std::cout << "Accepted client connection" << std::endl;
    send(clientSocket.fd, "Welcome to IRC Server Please Sign İn", 38, 0);
    server->clients.push_back(server->whenUserFirstJoin(server,clientSocket.fd));
    for (auto x : server->clients)
        std::cout << x.nickname << std::endl;
    //eğer user yaratıldıysa gerekli structlara atama yap. alt satırdaki gibi                                                   //binam burda kaldı
    //userMap[clientSocket] = client; //piltan da burda kalmış - map yapısı hata veriyo piltan. çözemedim. tutulmuyo sanırım pollfd ler mapte.

    return (0);
}

Server::Server(int port, char *paswd)
{
    this->index = 0;
    this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketFd == -1)
        std::cerr << "Failed to create socket" << std::endl;
    this->listeningSocket.fd = this->getSocketFd();
    this->listeningSocket.events = POLLIN;
    this->users.push_back(listeningSocket);
    this->hostName = "localhost";
    this->paswd = paswd;
    this->socketPort = port;
    std::cout << "Socket created" << std::endl;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); //bind to any available
    serverAddress.sin_port = htons(this->socketPort);
    try{
        if (bind(this->socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
            std::cerr << "Failed to bind socket" << std::endl;
    }
    catch(const std::exception& e){ //farklı bir port girilmeli
        std::cerr << e.what() << '\n';
    }
    if (listen(this->socketFd, this->userCount) == -1) //5 değişecektir
        std::cerr << "Failed to listen socket" << std::endl;

    std::cout << "Socket listening" << std::endl;
}

std::vector<struct pollfd> Server::getUsers()
{
    return users;
}

int Server::checkPasswd(char *paswd)
{
    if(strcmp(this->paswd.c_str(), paswd) == 0)
        return 1;
    else
        return 0;
}

int Server::getSocketFd()
{
    return this->socketFd;
}

int Server::clientDisconnect(Server *server, int i)//cmd quit
{
    std::cout << "Client disconnected" << std::endl;
    close(server->users[i].fd); // kapatılıp erase ile pollfd den siliniyor.
    server->users.erase(server->users.begin() + i);
    return -1;
}