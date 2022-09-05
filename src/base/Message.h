
#pragma once

namespace base
{

class Message {
    public:
        //void serialize() = 0;
    virtual std::string getData() = 0;
    private:
        //uint8_t* data_; 
};

class ProtobufMessage : public Message {
    public:
    //decode the message
        ProtobufMessage()
        {
            if(validate())
            {

            }
        }
    private:
        bool validate(){ return true; }
};

class StringMessage : public Message {
    public:
        StringMessage(char* data):message_(data){}
        std::string getData(){ return message_; }
    private:
        std::string message_;
};

}
