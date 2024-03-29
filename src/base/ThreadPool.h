
#pragma once

#include <functional>
#include <vector>
#include <thread>

#include <MessageQueue.h>
#include <StateMachine.h> //FIXME shouldn't know StateMachine, MessageDelivery?
#include <TcpServer.h> //FIXME shouldn't know TcpServer, MessageDelivery?

namespace base
{

class ThreadPool {
    public:
        class TcpServer;
        ThreadPool(std::shared_ptr<MessageQueue> queue):running_(false), queue_(queue){}
        void start(int numOfThreads)
        {
            running_ = true;
            threads_.reserve(numOfThreads);
            for(int i=0; i<numOfThreads; i++)
            {
                threads_.emplace_back(std::bind(&ThreadPool::runThread, this));
            }
        }

        void runThread()
        {
            while (running_)
            {
                queue_->wait();
                std::shared_ptr<Message> message = queue_->popFromQueue();
                std::cout << "processing message " << message->getData() << std::endl;
                stateMachine_->processEvent(message);
            }
        }

        void setStateMachine(std::shared_ptr<StateMachine> stateMachine) //FIXME
        {
            stateMachine_ = stateMachine;
        }

    private:
        bool running_;
        std::vector<std::thread> threads_;
        std::shared_ptr<MessageQueue> queue_;
        std::shared_ptr<StateMachine> stateMachine_;

};

}
