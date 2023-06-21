#include "Client.hpp"
#include "Server.hpp"

std::string parseNext(std::string param);

Client::Client()
{
    this->passwdcontrol = 0;
    this->isOperator = 0;
    this->clientAddressLength = sizeof(clientAddress);
    this->index = 0;
}

Client::~Client()
{
    //close(this->clientSocketfd);
}

/*void Client::cmdJoin(Client user, std::string cmd, std::string NextParameter) {
    
    std::map<std::string, std::vector<Client> >::iterator it = global._channels.begin();

    std::string parsedNext = parseNext(NextParameter);
    std::cout << "NextParameter: " << parseNext << std::endl;
    
    if(parsedNext.empty()) {
        std::cout << "Error: No channel name given." << std::endl;
        return;
    }
    while(it != global._channels.end()) {
        if(it->first == parsedNext) {
            it->second.push_back(user);
            myChannels.push_back(parsedNext);
            return;
        }
        it++;
    }
    //buraya bir kontrol eklenebilir -piltan
    std::vector<Client> newChannel;
    newChannel.push_back(user);
    global._channels.insert(std::pair<std::string, std::vector<Client> >(parsedNext, newChannel));

    myChannels.push_back(parsedNext);
}
*/

/*
void Client::cmdQuit(Client user, std::string cmd, std::string NextParameter) { Bulunduğun kanaldan çıkmak için i guess
    
    std::map<std::string, std::vector<Client> >::iterator it_map = global._channels.begin();
    std::vector<std::string>::iterator it_vec = this->myChannels.begin();
    std::vector<Client>::iterator it_client;
    (void)cmd;
    (void)NextParameter;
    this->users.erase(this->client_id);

    if(!this->myChannels.empty())
    {
        while(it_vec != this->myChannels.end())
        {
            it_map = global._channels.begin();
            while (it_map != global._channels.end())
            {
                if(it_map->first == *it_vec)
                {
                    it_client = std::find(it_map->second.begin(), it_map->second.end(), user);
                    if(it_client != it_map->second.end())
                    {
                        it_map->second.erase(it_client);
                    }
                    else
                    {
                        global._channels.erase(it_map);
                    }
                }
                it_map++;
            }
            it_vec++;
        }
    }
    //int Server::clientDisconnect(Server *server, int i) bu fonksiyona yönlendirin!
}
*/

/*void Client::cmdKick(Client user, std::string cmd, std::string NextParameter) {
    std::map<std::string, std::vector<Client> >::iterator it_map = global._channels.begin();
    std::vector<std::string>::iterator it_vec = this->myChannels.begin();

    std::string parsedNext = parseNext(NextParameter);

    if(parsedNext.empty()) {
        std::cout << "Error: No channel name given." << std::endl;
        return;
    }


}*/

/*
void Client::cmdPing(Client user, std::string cmd, std::string NextParameter) {
    //std::cout << "PONG!" << std::endl;
    ;
}

void Client::cmdNotice(Client user, std::string cmd, std::string NextParameter) {
    ;
}

//Şuraya kanal oluşturma fonk. koymam lazım bide.  of bi de bana koysana

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


int Client::joinServerIdentity(Client *client, std::string str)  //burayı binam olarak kullanacağım
{
    if (std::strcmp(str.c_str(), this->paswd.c_str()) == 0 || client->passwdcontrol == 1)
    {
        index++;
        client->passwdcontrol = 1;
        if (index == 2)
            client->username = str;
        else if (index == 3)
        {
            std::cout << "str" << std::endl;
            client->nickname = str;
            return(1);
        }
    }
    if (!client->passwdcontrol)
        return (-1);
    return (0);
}//when User first requested, we check passwd. Last create Identity.

/*
std::string parseNext(std::string param)
{
    std::string next;
    int i = 0;
    while (param[i] != ' ' && param[i] != '\0')
        i++;
    if (param[i] == '\0')
        return (NULL);
    i++;
    while (param[i] != ' ' && param[i] != '\0')
    {
        next += param[i];
        i++;
    }
    return (next);
}
*/