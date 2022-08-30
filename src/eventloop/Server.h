
//Called when there is a connection
static void
listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
    struct event_base *base = (struct event_base*)user_data;
    struct bufferevent *bev;

    //Construct a bufferevent
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev) {
        fprintf(stderr, "Error constructing bufferevent!");
        event_base_loopbreak(base);
        return;
    }

    //Binding read event callback function, write event callback function, error event callback function
    bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, NULL);

    bufferevent_enable(bev, EV_WRITE);
    bufferevent_enable(bev, EV_READ);

    const char *szMsg = "hi client!";
    bufferevent_write(bev, szMsg, strlen(szMsg));
}

class Server {
    public:
        Server(sockaddr_in sin, EventLoop* el):el_(el),sin_(sin){};
        void start() {
            auto listener = evconnlistener_new_bind(el.base(), listener_cb, (void *)base,
                                               LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
                                               (struct sockaddr*)&sin,
                                               sizeof(sin));
        }

    private:
        EventLoop* el_
        Address address_;
};
