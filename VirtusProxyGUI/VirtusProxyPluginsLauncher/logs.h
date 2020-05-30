#ifndef LOGS_H
#define LOGS_H
#include <QList>
class Message;
/*!
 *  class describing the list of messages
 */
class Logs
{
public:
    Logs(const QList<Message> & logs);
    Message message(int i) const;
    ~Logs();
    int size();
    const QList<Message> & getLogs() const;
private:
    const QList<Message> & logs;
};

#endif // LOGS_H
