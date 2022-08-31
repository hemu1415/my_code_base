
class TcpServer {
    public:
        TcpServer(Address address, EventLoop* eventLoop):address_(address),eventLoop_(eventLoop):acceptor_(new Acceptor())
        {
            acceptor_->setConnectionCallback(&TcpServer::addNewConnection, this);
        };

        void addNewConnection()
        {
            //connection pool?
            TcpConnecton tcpConnection = new TcpConnection();
            tcpConnection.setCB();
            connections_.push(tcpConnection);
        }
    private:
        Address address_;
        EventLoop* eventLoop_
        std::unique_ptr<Acceptor> acceptor_;
        std::vector<TcpConnection> connections_;
};
