
#pragma once

#include <EventLoop.h>
#include <BufferEvent.h>

using namespace libevent;

namespace base
{

class TcpConnection {
    public:
        TcpConnection()=default;
        TcpConnection(std::shared_ptr<EventLoop> eventLoop, evutil_socket_t sock):bufferEvent_(eventLoop->getBase(), sock)
        {
        }

        void setCB(const BufferEvent::EventCallback& readCb, const BufferEvent::EventCallback& writeCb)
        {
            bufferEvent_.setCB(readCb, writeCb);
        }

    private:
        BufferEvent bufferEvent_;
};

}
