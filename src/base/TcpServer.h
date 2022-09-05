
#pragma once

#include <functional>
#include <vector>

#include <TcpConnection.h>
#include <Acceptor.h>
#include <Address.h>
#include <MessageQueue.h>
#include <ThreadPool.h>

using namespace std::placeholders;

namespace base
{

class TcpServer {
    public:
        TcpServer(Address address, std::shared_ptr<EventLoop> eventLoop):address_(address),eventLoop_(eventLoop),
                                   acceptor_(new Acceptor(eventLoop, address)),
                                   messageQueue_(new MessageQueue),
                                   threadPool_(messageQueue_) //FIXME
        {
            connections_.reserve(10);
        };

        void start()
        {
            acceptor_->setConnectionCallback(&TcpServer::addNewConnection, this);
            threadPool_.start(1); //TODO read from config
            eventLoop_->loop();
        }

        std::shared_ptr<EventLoop> getEventLoop() { return eventLoop_; }

        void addConnection(evutil_socket_t sock)//FIXME
        {
            //TODO the vector connections must reserve some, otherwise when add new connection, the vector will relocate
            //which will call move constructor(noexcept), otherwise it will call copy constructor(in this case) and then
            //deconstructor, then the first connection will be destroyed!!!
            connections_.emplace_back(eventLoop_, sock);
            TcpConnection& connection = connections_.back();
            connection.setCB(&TcpServer::readCallback, &TcpServer::writeCallback, this);
        }

        static void addNewConnection(struct evconnlistener *listener, evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr); //MUST be const!
        static void readCallback(struct bufferevent* bev, void *ptr);
        static void writeCallback(struct bufferevent* bev, void *ptr);

    private:
        Address address_;
        std::shared_ptr<MessageQueue> messageQueue_;
        ThreadPool threadPool_;
        std::shared_ptr<EventLoop> eventLoop_;
        std::unique_ptr<Acceptor> acceptor_;
        std::vector<TcpConnection> connections_;
};

}
