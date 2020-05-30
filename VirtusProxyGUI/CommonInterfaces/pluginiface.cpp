#include "connectioniface.h"
#include "message.h"
#include "pluginiface.h"

PluginIFace::PluginIFace(QString _name, QString _version, QIcon _icon):QObject(nullptr)
{
    this->_version = _version;
    this->_icon = _icon;
    this->_name = _name;
}

PluginIFace::~PluginIFace()
{
    this->_connectedIFaces.clear();
}

QList<Message> PluginIFace::messageList()
{
    QList<Message> messages;
    foreach(auto& iface, this->_connectedIFaces)
    {
        messages.append(iface->messageList());
    }
    return messages;
}


QString PluginIFace::name() const
{
    return this->_name;
}

QList<QSharedPointer<ConnectionIFace>> & PluginIFace::connectedIFaces()
{
    return this->_connectedIFaces;
}

QString PluginIFace::version() const
{
    return _version;
}

QString PluginIFace::id()
{
    return QString();
}

QIcon PluginIFace::icon(){
    return _icon;
}


void PluginIFace::change()
{
    emit connectionIFaceChanged();
}

void PluginIFace::messageReceived(const Message & message)
{
    emit received(message);
}
void PluginIFace::messageSended(const Message & message)
{
    emit sended(message);
}

void PluginIFace::addConnectionIFace(ConnectionIFace* iface)
{
    this->_connectedIFaces.push_back(QSharedPointer<ConnectionIFace>(iface));
    QObject::connect(iface, &ConnectionIFace::connectionStatusChanged, this, &PluginIFace::change);
    QObject::connect(iface, &ConnectionIFace::messageSended, this, &PluginIFace::messageSended);
    QObject::connect(iface, &ConnectionIFace::messageReceived, this, &PluginIFace::messageReceived);
}
