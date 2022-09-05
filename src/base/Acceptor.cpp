
#include <Acceptor.h>

using namespace base;

void Acceptor::setConnectionCallback(EvconnListener::ConnectionCallback cb, void* arg)
{
    listener_.setCB(cb, arg);
}
