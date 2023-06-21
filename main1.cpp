#include <iostream>
#include <string.h>

int main(int ac, char **av)
{
    std::string buffer;

    if (ac > 1)
        buffer = av[1];
    std::cout << buffer << std::endl;
}