#include "Client.hpp"
#include "Server.hpp"

Client::Client()
{
    this->passwdcontrol = 0;
    this->index = 0;
}

Client::~Client()
{
    //close(this->clientSocketfd);
}

void Client::joinChannelIdentity(std::string str)
{
    if (std::strcmp(str.c_str(), this->paswd.c_str()) == 0 || this->passwdcontrol == 1)
    {
        this->index++;
        this->passwdcontrol = 1;
        if (index == 2)
            this->username = str;
        else if (index == 3)
            this->nickname = str;
    }
}//when User first came, we check passwd. Last create Identity.