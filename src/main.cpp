#include <iostream>

#include <Address.h>
#include <EventLoop.h>
#include "TraceManager.h"

int main()
{
    Address address("127.0.0.1", 12345);
    auto eventLoop = std::make_shared<EventLoop>();
    TraceManager traceManager(address, eventLoop);
    traceManager.start(); //BLOCK HERE

    return 0;
}

