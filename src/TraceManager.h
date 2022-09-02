
#pragma once

#include <TcpServer.h>
#include <Address.h>

using namespace base;

class TraceManager {
    public:
        TraceManager(Address address, std::shared_ptr<EventLoop> eventLoop):server_(address, eventLoop){};
        void start()
        {
            server_.start();
        }

    private:
        TcpServer server_;
        //TraceManagerStateMachine stateMachine_;
        //std::vector<DataProvider> dataProviders_;
        //std::queue<Event> eventQueue_;
};
