
#pragma once

struct Register {
    std::string message;
};

class StateMachine {
    public:
        virtual void processEvent(Register event) = 0;
};
