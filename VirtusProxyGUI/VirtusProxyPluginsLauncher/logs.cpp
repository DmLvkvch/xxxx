#include "logs.h"
#include "message.h"

Logs::Logs(const QList<Message> & logs):logs(logs)
{
}

Message Logs::message(int i) const{
    return this->logs.at(i);
}

int Logs::size()
{
    return this->logs.size();
}

const QList<Message> & Logs::getLogs() const
{
    return this->logs;
}

Logs::~Logs()
{

}
