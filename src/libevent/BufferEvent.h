
#pragma once

#include <functional>
#include <memory>

#include <event2/bufferevent.h>

namespace libevent
{

class BufferEvent {
    public:
        using EventCallback=std::function<void(struct bufferevent *bev, void *ctx)>;

    public:
        BufferEvent(EventBase eventBase, evutil_socket_t fd)
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

        void setCB(EventCallback readCallback, EventCallback writeCallback)
        {
            //Binding read event callback function, write event callback function, error event callback function
            bufferevent_setcb(bev_, readCallback.target<void(struct bufferevent *bev, void *ctx)>(),
                                    writeCallback.target<void(struct bufferevent *bev, void *ctx)>(),
                                    NULL, NULL);

            bufferevent_enable(bev_, EV_WRITE);
            bufferevent_enable(bev_, EV_READ);

        }
    private:
        struct bufferevent* bev_;
};

};
