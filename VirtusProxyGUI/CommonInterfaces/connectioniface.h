#ifndef IFACE_H
#define IFACE_H

#include <QIcon>
#include <QString>
#include <QObject>
#include "commoninterfaces_global.h"
class Message;
class SettingsItem;
/*!
 *  class describing the connected interface
 */
class COMMONINTERFACES_EXPORT ConnectionIFace:public QObject
{
    Q_OBJECT
public:
    enum class Status{ ///status of connection
        Unknown, Connected, Disconnected
    };
    /*!
      * \brief Конструктор объекта класса ConnectionIFace
      * инициализирует все настройки подключенного интерфейса
      */
    ConnectionIFace(QString _name, QList<SettingsItem> _settings);
    QString name() const;///<имя интерфейса
    Status status() const;///<статус интерфейса
    void setSettings(const QList<SettingsItem> & settings);///<установить настройки интерфеса
    QList<SettingsItem> & settings();///<получить настройки
    QList<Message> & messageList();///<список сообщений
    QIcon icon() const;
    virtual void send(const Message & message) = 0;///<отправить сообщение
    virtual void receive(const Message & message) = 0;///<получение сообщения
    virtual void connect() = 0;
    virtual ~ConnectionIFace();
private slots:
    void setStatus(Status status);
signals:
    void messageReceived(const Message & message);
    void messageSended(const Message & message);
    void connectionStatusChanged(Status status);
protected:
    void setIconPath(QString path);
    QList<Message> _messages;
private:
    QString _iconPath;
    QString _name;
    Status _status;
    QList<SettingsItem> _settings;
};

#endif // IFACE_H
