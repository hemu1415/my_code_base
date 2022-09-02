
#include <iostream>
#include <memory>

#include <TcpServer.h>
#include <BufferEvent.h>
#include <TcpConnection.h>

using namespace base;
using namespace std::placeholders;

void TcpServer::addNewConnection(struct evconnlistener *listener, evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr) //raw libevent interface exposed here, FIXME
{
    std::cout << "create new connection" << std::endl;

    //connection pool?
    auto tcpConnection = std::make_shared<TcpConnection>(eventLoop_, sock);

    tcpConnection->setCB(std::bind(&TcpServer::readCallback, this, _1, _2), 
                         std::bind(&TcpServer::writeCallback, this, _1, _2));
    connections_.push_back(*tcpConnection); //change TcpServer obj, the callback cann't be const
}

void TcpServer::readCallback(struct bufferevent* bev, void *ptr) const
{
    std::cout << "TcpServer::readCallback" << std::endl;
}

void TcpServer::writeCallback(struct bufferevent* bev, void *ptr) const
{
}

