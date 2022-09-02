
#pragma once

#include <functional>

#include <TcpConnection.h>
#include <Acceptor.h>
#include <Address.h>

using namespace std::placeholders;

namespace base
{

class TcpServer {
    public:
        TcpServer(Address address, std::shared_ptr<EventLoop> eventLoop):address_(address),eventLoop_(eventLoop),
                                   acceptor_(new Acceptor(eventLoop, address, std::bind(&TcpServer::addNewConnection, this, _1, _2, _3, _4, _5)))
        {
        };

        void start() { eventLoop_->loop(); }


        void addNewConnection(struct evconnlistener *listener, evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr); //MUST be const!
        void readCallback(struct bufferevent* bev, void *ptr) const;
        void writeCallback(struct bufferevent* bev, void *ptr) const;

    private:
        Address address_;
        std::shared_ptr<EventLoop> eventLoop_;
        std::unique_ptr<Acceptor> acceptor_;
        std::vector<TcpConnection> connections_;
};

}
