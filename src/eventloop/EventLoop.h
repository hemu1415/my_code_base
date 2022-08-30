
class EventLoop {
    public:
        using std::function<>=;
        EventLoop(event_base* base):base_(base){};
        event_base* base(){return base_}
        setReadCB(){}
        setWriteCB(){}
        ~EventLoop()
        {
            evconnlistener_free(listener);
            event_base_free(base);
        };
        void loop()
        {
            event_base_dispatch(base_);
        }
    private:
        struct event_base* base_;

};

class EventLoopFactory {
    public:
        EventLoop createEventLoop() {
            return EventLoop(event_base_new());
        }
};
