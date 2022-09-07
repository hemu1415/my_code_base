
#include <iostream>
#include <memory>

#include <event2/buffer.h> //FIXME, remove me

#include <TcpServer.h>
#include <BufferEvent.h>
#include <TcpConnection.h>

using namespace base;
using namespace std::placeholders;

void TcpServer::newConnectionCallback(struct evconnlistener *listener, evutil_socket_t sock, struct sockaddr *addr, int len, void *ptr) //raw libevent interface exposed here, FIXME
{
    std::cout << "create new connection" << std::endl;

    //connection pool?
    TcpServer* server = static_cast<TcpServer*>(ptr);
    
    //FIXME TcpConnection having bufferevent, can not be copy and destroy
    server->addConnection(sock);
}

void TcpServer::readCallback(struct bufferevent* bev, void *ptr)
{
    std::cout << "TcpServer::readCallback" << std::endl;

    TcpServer* server = static_cast<TcpServer*>(ptr);

    struct evbuffer *input = bufferevent_get_input(bev); //FIXME
    size_t sz = evbuffer_get_length(input);
    if(sz > 0)
    {
        char buf[256] = {0};
        bufferevent_read(bev, buf, sz);
        auto message = std::make_shared<StringMessage>(buf);
        server->messageQueue_->pushInQueue(message);
    }
}

void TcpServer::writeCallback(struct bufferevent* bev, void *ptr)
{
}

