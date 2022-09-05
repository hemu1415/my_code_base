
#include <functional>
#include <vector>
#include <thread>

#include <MessageQueue.h>

namespace base
{

class ThreadPool {
    public:
        ThreadPool(std::shared_ptr<MessageQueue> queue):running_(false), queue_(queue){}
        ~ThreadPool() = default;
        void start(int numOfThreads)
        {
            running_ = true;
            threads_.reserve(numOfThreads);
            for(int i=0; i<numOfThreads; i++)
            {
                threads_.emplace_back(std::bind(&ThreadPool::runInThread, this));
            }
        }

        void runInThread()
        {
            while (running_)
            {
                queue_->wait();
                auto message = queue_->popFromQueue();
                std::cout << "processing message " << message->getData() << std::endl;
            }
        }

    private:
        bool running_;
        std::vector<std::thread> threads_;
        std::shared_ptr<MessageQueue> queue_;
};

}
