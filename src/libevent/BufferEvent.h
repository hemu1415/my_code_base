
#pragma once

#include <functional>
#include <memory>

#include <event2/bufferevent.h>

namespace libevent
{
/**
 * Bufferevents currently only work for stream-oriented protocols like TCP.
 * There may in the future be support for datagram-oriented protocols like UDP.
 * 
 */

class BufferEvent {
    public:
        //using EventCallback=std::function<void(struct bufferevent *bev, void *ctx)>;
        typedef void (*EventCallback)(struct bufferevent *bev, void *ctx);

    public:
        BufferEvent(const EventBase& eventBase, evutil_socket_t fd)
        {
            bev_ = bufferevent_socket_new(eventBase, fd, BEV_OPT_CLOSE_ON_FREE);
            if (!bev_) {
                //throw exception
                std::cerr << "Error constructing bufferevent!" << std::endl;
                event_base_loopbreak(eventBase);
                return;
            }
            else
                std::cout << "bufferevent_socket_new success" << std::endl;
        }

        operator struct bufferevent*() const { return bev_; }

        ~BufferEvent()
        {
            std::cout << "free buffer event" << std::endl;
            bufferevent_free(bev_);
        }

        void setCB(EventCallback readCallback, EventCallback writeCallback, void *cbarg)
        {
            //Binding read event callback function, write event callback function, error event callback function
            bufferevent_setcb(bev_, readCallback, writeCallback, NULL, cbarg);

            bufferevent_enable(bev_, EV_WRITE);
            bufferevent_enable(bev_, EV_READ);

        }
    private:
        struct bufferevent* bev_;
};

};
