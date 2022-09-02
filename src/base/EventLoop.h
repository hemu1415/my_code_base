
#pragma once

#include <event2/event.h> //it's not good to expose this interface to user

#include <EventBase.h>

using namespace libevent;

namespace base
{

class EventLoop {
    public:
        EventLoop(){std::cout << "EventLoop ctor" << std::endl;}
        ~EventLoop(){std::cout << "EventLoop dtor" << std::endl;}

        EventBase& getBase() { return base_; } //use reference to avoid copy, use shared_ptr<EventBase> instead. FIXME

        void loop()
        {
            base_.loop();
        }
    private:
        EventBase base_;
};

}
