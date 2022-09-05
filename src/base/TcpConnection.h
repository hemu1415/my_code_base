
#pragma once

#include <EventLoop.h>
#include <BufferEvent.h>

using namespace libevent;

namespace base
{

class TcpConnection {
    public:
        TcpConnection()=default;
        TcpConnection(std::shared_ptr<EventLoop> eventLoop, evutil_socket_t sock):bufferEvent_(eventLoop->getBase(), sock) //FIXME drop Eventloop, pass EventBase
        {
            std::cout << "TcpConnection ctor" << std::endl;
        }

        ~TcpConnection()
        {
            std::cout << "TcpConnection detor" << std::endl;
        }

        void setCB(BufferEvent::EventCallback readCb, BufferEvent::EventCallback writeCb, void *cbarg)
        {
            bufferEvent_.setCB(readCb, writeCb, cbarg);
        }

    private:
        BufferEvent bufferEvent_;
};

}
