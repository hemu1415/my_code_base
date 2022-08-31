
class TraceManager {
    public:
        TraceManager();

    private:
        TcpServer server_;
        TraceManagerStateMachine stateMachine_;
        std::vector<DataProvider> dataProviders_;
        std::queue<Event> eventQueue_;
};
