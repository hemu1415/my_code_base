
class DataProvider {
    public:

    private:
        DataProviderStateMachine stateMachine;
        TcpConnection connection_;
        std::queue<Event> eventQueue_;
};
