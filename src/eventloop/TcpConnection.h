
class TcpConnection {
    public:
        TcpConnection();

        setCB()
        {
            //Binding read event callback function, write event callback function, error event callback function
            bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, NULL);
        
            bufferevent_enable(bev, EV_WRITE);
            bufferevent_enable(bev, EV_READ);

        }

        write(uint8_t* message)
        {
            bufferevent_write(bev, message, strlen(message));

        }

    private:
        Buffer buffer;
};
