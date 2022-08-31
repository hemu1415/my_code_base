
class Acceptor {
    public:
        using std::function<> = ConnectionCallback; 

    public:
        explicit Acceptor(const Address& address, ConnectionCallback cb):address_(address),connectionCallback_(cb)
        {
            //Create, bind and listen to socket
            listener_ = evconnlistener_new_bind(base, connectionCallback_.target(), (void *)base,
                                               LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                               (struct sockaddr*)&sin,
                                               sizeof(sin));
            if (!listener) {
                throw
            }    
        }
        void setConnectionCallback();
        ~Acceptor()
        {
            evconnlistener_free(listener);
        }
    private:
        struct evconnlistener* listener_;
        ConnectionCallback connectionCallback_;
        Socket socketFd_;
        Address address_;
};
