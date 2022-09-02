
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
        Acceptor(std::shared_ptr<EventLoop> eventLoop, const Address& address, EvconnListener::ConnectionCallback cb):
                                                eventLoop_(eventLoop),
                                                address_(address),
                                                connectionCallback_(cb),
                                                listener_(eventLoop->getBase(), address.getSockAddr(), cb){}
        void setConnectionCallback();
        ~Acceptor(){}
    private:
        std::shared_ptr<EventLoop> eventLoop_;
        Address address_;
        EvconnListener::ConnectionCallback connectionCallback_;
        EvconnListener listener_;
};

}
