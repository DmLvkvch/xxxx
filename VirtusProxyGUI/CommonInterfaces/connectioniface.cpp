#include "connectioniface.h"
#include "message.h"
#include "settingsitem.h"
#include <QDebug>

ConnectionIFace::ConnectionIFace(QString _name, QList<SettingsItem> _settings)
{
    this->_name = _name;
    this->_settings = _settings;
    this->_status = ConnectionIFace::Status::Unknown;
    QObject::connect(this, &ConnectionIFace::connectionStatusChanged, this, &ConnectionIFace::setStatus);
}

ConnectionIFace::~ConnectionIFace()
{
    _settings.clear();
}

void ConnectionIFace::setStatus(Status _status){
    this->_status = _status;
}

void ConnectionIFace::setIconPath(QString path)
{
    this->_iconPath = path;
}

QIcon ConnectionIFace::icon() const
{
    QIcon icon(this->_iconPath);
    return icon;
}

QString ConnectionIFace::name() const
{
    return this->_name;
}

ConnectionIFace::Status ConnectionIFace::status() const
{
    return this->_status;
}

void ConnectionIFace::setSettings(const QList<SettingsItem> & /*settings*/)
{

}

QList<Message> & ConnectionIFace::messageList()
{
    return this->_messages;
}

QList<SettingsItem> & ConnectionIFace::settings(){
    return this->_settings;
}
