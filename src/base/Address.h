
#pragma once

#include <string>
#include <cstdint>
#include <regex>

#include <netinet/in.h>

namespace base
{

class Address {
    public:
        Address(std::string ip, uint16_t port);//ip can be 'ipv4', 'ipv6', 'INADDR_ANY', 'INADDR_LOOPBACK'
        struct sockaddr_in getSockAddr() const { return addr_; }

        //interface inspecting Address
        std::string ip();
        uint16_t port();

    private:
        bool validate(const std::string& ip)
        {
            std::regex ipv4(pattern);
            return std::regex_match(ip, ipv4)?true:false;
        }

    private:
        const std::string pattern = "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
        struct sockaddr_in addr_;

};

}
