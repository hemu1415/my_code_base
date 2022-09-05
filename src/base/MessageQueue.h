
#pragma once

#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>

#include <Message.h>

namespace base
{

//TODO template?
class MessageQueue {
    public:
        void pushInQueue(std::shared_ptr<Message> message)
        {
            queue_.push(message);
            notify();
        }
        std::shared_ptr<Message> popFromQueue()
        {
            auto message = queue_.front();
            queue_.pop();
            return message;
        }
        size_t getSize() { return queue_.size(); }
        void notify()
        {
            std::unique_lock<std::mutex> lck(mtx);
            cv.notify_one();
        }
        void wait()
        {
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck);
        }
    private:
        std::mutex mtx;
        std::condition_variable cv;
        //FIXME thread-safe
        std::queue<std::shared_ptr<Message>> queue_;
};

}
