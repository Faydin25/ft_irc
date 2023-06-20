#include <iostream>
#include <map>
#include <vector>
#include "Client.hpp"
int main() {
    std::map <std::string, std::vector<Client> > ChannelAndId;
    ChannelAndId["Channel1"].push_back("Id1");
    ChannelAndId["Channel2"].push_back("Id2");
    ChannelAndId["Channel3"].push_back("Id3");
    ChannelAndId["Channel4"].push_back("Id4");

    std::map<std::string, std::vector<std::string> >::iterator it;

    for (it = ChannelAndId.begin(); it != ChannelAndId.end(); ++it) {
        std::cout << it->first << ": ";
        std::vector<std::string>& ids = it->second;
        for (size_t i = 0; i < ids.size(); ++i) {
            std::cout << ids[i] << " ";
        }
        std::cout << std::endl;
    }
}
