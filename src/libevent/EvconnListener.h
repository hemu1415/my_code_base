
#pragma once

#include <event2/listener.h>

namespace libevent
{

class EvconnListener {
    public:
        //using ConnectionCallback = std::function<void(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int, void*)>;
        typedef void (*ConnectionCallback)(struct evconnlistener*, evutil_socket_t, struct sockaddr*, int, void*);

    public:
        EvconnListener(const EventBase& base, struct sockaddr_in addr)
        {
            std::cout << "EvconnListener ctor" << std::endl;
            //Create, bind and listen to socket, cb set to NULL, the listener is disabled.
            listener_ = evconnlistener_new_bind(base, NULL, NULL,
                                               LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                               (struct sockaddr*)&addr,
                                               sizeof(addr));
            if (!listener_) {
                //throw exception
                std::cerr << "evconnlistener_new_bind() error" << std::endl;
            }
            else
                std::cout << "evconnlistener_new_bind() success" << std::endl;


        }

        void setCB(ConnectionCallback cb, void* arg)
        {
            evconnlistener_set_cb(listener_, cb, arg);
        }

        operator struct evconnlistener*() const { return listener_; }

        ~EvconnListener()
        {
            std::cout << "free listener" << std::endl;
            evconnlistener_free(listener_);
        }
    private:
        struct evconnlistener* listener_;
};

}
