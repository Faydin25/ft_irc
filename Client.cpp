#include "Client.hpp"
#include "Server.hpp"

Client::Client()
{
    this->passwdcontrol = 0;
    this->isOperator = 0;
    this->clientAddressLength = sizeof(clientAddress);
}

Client::~Client()
{
    //close(this->clientSocketfd);
}

void Client::sendMessageToChannel(Client user, std::string channelName) {
    std::map<std::string, std::vector<Client> > channels = this->getChannels();
    std::map<std::string, std::vector<Client> >::iterator it;
    try{
        it = channels.find(channelName);
        if (it != channels.end()) {
            std::cout << "(!)" << channelName << " has been found by " << user.nickname << "." << std::endl;
        }
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/*
void Client::cmdJoin(Client user, std::string cmd, std::string NextParameter) {
    ;
}

void Client::cmdQuit(Client user, std::string cmd, std::string NextParameter) {
    ;
}

void Client::cmdKick(Client user, std::string cmd, std::string NextParameter) {
    ;
}

void Client::cmdPing(Client user, std::string cmd, std::string NextParameter) {
    //std::cout << "PONG!" << std::endl;
    ;
}

void Client::cmdNotice(Client user, std::string cmd, std::string NextParameter) {
    ;
}

//Şuraya kanal oluşturma fonk. koymam lazım bide.

void Client::FindCommands(Client user, std::string cmd, std::string NextParameter)
{
    //Parse and control input.
    if (strcmp(cmd.c_str(), "JOIN") == 0)
    {
        //NextParameter direkt kanalımız oluyor. Kanal var mı kontrol et. Varsa kullanıcıyı kanala ekle.(buna int yetti ama turkçe düşünüp cevirdim xd ondan sildim)
    }
    else if (strcmp(cmd.c_str(), "QUIT") == 0)
    {
        //NextParameter direkt kanalımız oluyor. Kanal var mı kontrol et. Varsa kullanıcı kanaldan çıkış yapsın.(buna ingilizcem yetmedı aq)
    }
    else if (strcmp(cmd.c_str(), "PRIVMSG") == 0)
    {
        //I have the written notices , I was lazy...
    }
    else if (strcmp(cmd.c_str(), "NOTICE") == 0)
    {

    }
    else if (strcmp(cmd.c_str(), "PING") == 0)//If cmd is "PING". be carefull for NextParameter(I dont want segF... ty)
    {

    }
    else
        std::cout << "Wrong Commands!" << std::endl;
}

//----------------------------------------------------------------------------------------
*/

int Client::joinServerIdentity(std::string str)
{
    int index = 0;
    if (std::strcmp(str.c_str(), this->paswd.c_str()) == 0 || this->passwdcontrol == 1)
    {
        index++;
        this->passwdcontrol = 1;
        if (index == 2)
            this->username = str;
        else if (index == 3)
        {
            this->nickname = str;
            return(1);
        }
    }
    if (!this->passwdcontrol)
        return (-1);
    return (0);
}//when User first requested, we check passwd. Last create Identity.

std::map<std::string, std::vector<Client> > Client::getChannels()
{
    return this->_channels;
}

std::vector<Client> Client::getChannelUsers(std::string channelName)
{
    if(this->_channels.find(channelName) != this->_channels.end())
        return this->_channels[channelName];
    else
        return std::vector<Client>();
}

void Client::createChannel(std::string channel_name, Client &user) {
    this->_channels[channel_name].push_back(user);
}