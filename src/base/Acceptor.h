
#pragma once

#include <functional>
#include <iostream>
#include <memory>

#include <Address.h>
#include <EventLoop.h>
#include <EvconnListener.h>

namespace base
{

class Acceptor {
    public:
        Acceptor(std::shared_ptr<EventLoop> eventLoop, const Address& address):
                                                eventLoop_(eventLoop),
                                                address_(address),
                                                listener_(eventLoop->getBase(), address.getSockAddr()){}
        void setConnectionCallback(EvconnListener::ConnectionCallback cb, void* arg);
        ~Acceptor(){}
    private:
        std::shared_ptr<EventLoop> eventLoop_;
        Address address_;
        EvconnListener listener_;
};

}
