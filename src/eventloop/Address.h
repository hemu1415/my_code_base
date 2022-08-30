#include <string>
#include <cstdint>

#include <netinet/in.h>

class Address {
    public:
        Address(std::string ip, uint16_t port)//ip can be 'ipv4', 'ipv6', 'INADDR_ANY', 'INADDR_LOOPBACK'
        {
            //validate ip pattern, if fail, the data member would not be destructed!!!
            if !valid throw error;

        }
        std::string ip();
        uint16_t port();

    private:
        //std::variant
        struct sockaddr_in addr_;
        struct sockaddr_in6 addr6_;


};
