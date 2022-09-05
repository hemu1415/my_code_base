
#pragma once

#include <event2/event.h>

namespace libevent
{
    class EventBase { //if EventBase is copyable, after that it will be released. FIXME
        public:
            EventBase()
            {
                base_=event_base_new();
                if(base_ == NULL)
                    //throw exception
                    std::cerr << "event_base_new() error" << std::endl;
                else
                    std::cout << "event_base_new() success " << base_ << std::endl;
            }

            void loop()
            {
                std::cout << "start loop" << std::endl;
                int ret = event_base_dispatch(base_);
                std::cout << "end loop: " << ret << std::endl;
            }

            operator struct event_base*() const { return base_; }

            ~EventBase() {
                std::cout << "free event base" << std::endl;
                event_base_free(base_);
            }

        private:
            struct event_base* base_;
    };
}
