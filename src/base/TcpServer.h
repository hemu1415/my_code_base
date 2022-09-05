
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
            connections_.emplace_back(eventLoop_, sock); //change TcpServer obj, the callback cann't be const
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
