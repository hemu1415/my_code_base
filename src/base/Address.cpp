#include <arpa/inet.h>
#include <iostream>

#include <Address.h>

using namespace base;

Address::Address(std::string ip, uint16_t port)
{
    //validate ip pattern, if fail, the data member would not be destructed!!!
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &(addr_.sin_addr));

}

std::string Address::ip()
{
    char ip[INET_ADDRSTRLEN];
    return std::string(inet_ntop(AF_INET, &(addr_.sin_addr), ip, INET_ADDRSTRLEN));
}

uint16_t Address::port()
{
    return ntohs(addr_.sin_port);
}
