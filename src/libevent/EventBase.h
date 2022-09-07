
#pragma once

#include <memory>

#include <event2/event.h>

namespace libevent
{
    class EventBase { //if EventBase is copyable, after that it will be released. FIXME
        public:
            EventBase():base_(event_base_new(), [](struct event_base* e){ event_base_free(e); }) //add a custom deleter to make EventBase obj copyable :)

            {
                if(base_.get() == NULL)
                    //throw exception
                    std::cerr << "event_base_new() error" << std::endl;
                else
                    std::cout << "event_base_new() success " << base_ << std::endl;
            }

            void loop()
            {
                std::cout << "start loop" << std::endl;
                int ret = event_base_dispatch(base_.get());
                std::cout << "end loop: " << ret << std::endl;
            }

            operator struct event_base*() const { return base_.get(); }

        private:
            std::shared_ptr<struct event_base> base_;
    };
}
