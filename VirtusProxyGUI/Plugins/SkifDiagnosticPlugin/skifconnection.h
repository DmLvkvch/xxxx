#ifndef SKIFCONNECTION_H
#define SKIFCONNECTION_H

#include "connectioniface.h"

class SkifConnection : public ConnectionIFace
{
    Q_OBJECT
public:
    SkifConnection();

    // ConnectionIFace interface
public:
    void send(const Message &message);
    void receive(const Message &message);
    void connect();
};

#endif // SKIFCONNECTION_H
