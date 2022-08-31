
class Buffer {
    public:
        Buffer()
        {
            bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
            if (!bev) {
                fprintf(stderr, "Error constructing bufferevent!");
                event_base_loopbreak(base);
                return;
            }
        }
    private:
        struct bufferevent *bev;

};
