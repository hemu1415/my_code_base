
#include <event2/buffer.h>

//Libevent’s evbuffer functionality implements a queue of bytes, optimized for adding data to the end and removing it from the front.

class Evbuffer {
    public:
        Evbuffer():evbuffer(evbuffer_new(void)) {}
        ~Evbuffer()
        {
            evbuffer_free(evbuffer_);
        }

        int read(void* data, size_t len)
        {
            evbuffer_remove(evbuffer_, data, len)
        }

    private:
        struct evbuffer* evbuffer_;
};
