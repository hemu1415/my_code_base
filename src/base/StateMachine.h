
#pragma once

#include <Message.h>

namespace base
{

class StateMachine {
    public:
        virtual void processEvent(std::shared_ptr<Message> event) = 0;
        virtual std::string getName() = 0;
};

}
