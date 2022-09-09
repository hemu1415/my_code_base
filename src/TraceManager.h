
#pragma once

#include <memory>

#include <TcpServer.h>
#include <Address.h>

#include "TraceManagerStateMachine.h"

using namespace base;

class TraceManager {
    public:
        TraceManager(Address address, std::shared_ptr<EventLoop> eventLoop):server_(address, eventLoop), stateMachine_(new TraceManagerStateMachine("hemu")){}
        void start()
        {
            server_.registerStateMachine(stateMachine_); //TODO if no, register a default state machine which print all event out
            server_.start(); //BLOCK HERE
        }

    private:
        TcpServer server_;
        std::shared_ptr<TraceManagerStateMachine> stateMachine_;
        //std::vector<DataProvider> dataProviders_;
};
