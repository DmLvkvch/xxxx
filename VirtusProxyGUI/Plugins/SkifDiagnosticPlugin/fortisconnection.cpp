#include "fortisconnection.h"
#include <QTimer>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include "message.h"
#include "settingsitem.h"
#define CHECK_STATE_TIME_INTERVAL_MSEC (10000)
#define FORCE_PING_TIME_INTERVAL_MSEC (5000)

FortisConnection::FortisConnection(QUrl url):ConnectionIFace(tr("Фортис"), QList<SettingsItem>()
                                                             <<SettingsItem("IP", url.host(),SettingsItem::Type::Ip, 0, 0, 0, 0 )
                                                             <<SettingsItem("port", url.port(),SettingsItem::Type::Port, 0, 0, 0, 0 ))
{
    this->_url = url;
    _webSocket = new QWebSocket();
    QObject::connect(_webSocket, &QWebSocket::connected,
                this, &FortisConnection::onConnected,
                Qt::UniqueConnection);
    QObject::connect(_webSocket, &QWebSocket::disconnected,
                this, &FortisConnection::onDisconnected,
                Qt::UniqueConnection);
    QObject::connect(_webSocket, &QWebSocket::connected,
                this, &FortisConnection::connected,
                Qt::UniqueConnection);
    QObject::connect(_webSocket, &QWebSocket::disconnected,
                this, &FortisConnection::disconnected,
                Qt::UniqueConnection);
    setIconPath(":/images/res/forts_startLogo.png");
}

void FortisConnection::connect()
{
    reconnect();
    QTimer::singleShot(CHECK_STATE_TIME_INTERVAL_MSEC, this, SLOT(checkState()));
    QTimer::singleShot(FORCE_PING_TIME_INTERVAL_MSEC, this, SLOT(forcePing()));
}

void FortisConnection::send(const Message & message)
{
    this->_messages.push_back(message);
    emit messageSended(message);
}

void FortisConnection::receive(const Message &message)
{
    this->_messages.push_back(message);
    emit messageReceived(message);
}

FortisConnection::~FortisConnection()
{
    if (_webSocket)
    {
        delete _webSocket;
    }
}

void FortisConnection::onDisconnected()
{
    if (!_isConnected)
    {
        return;
    }
    emit connectionStatusChanged(Status::Disconnected);
    qDebug() << "WebSocket was disconnected...";
    _isConnected = false;
    _isDronesReceived = false;
    _drones.clear();
    _lastReceivedTime.clear();
    reconnect();
}

void FortisConnection::reconnect()
{
    if (_isConnected)
    {
        return;
    }
    if (_webSocket == nullptr)
    {
        return;
    }
    qDebug() << "Attempt to connect on" << _url.toString();
    Q_ASSERT(_webSocket);
    _webSocket->open(_url);
    QTimer::singleShot(2000, this, SLOT(reconnect()));
}

void FortisConnection::onConnected()
{
    _isConnected = true;
    emit connectionStatusChanged(Status::Connected);
    qDebug() << "WebSocket connected on" << _url.toString();
    Q_ASSERT(_webSocket);
    QObject::connect(_webSocket, &QWebSocket::textMessageReceived,
            this, &FortisConnection::onTextMessageReceived,
                                    Qt::UniqueConnection);
    getDrones();
}

void FortisConnection::getDrones()
{
    if (_isDronesReceived)
    {
        return;
    }
    if (_webSocket == nullptr)
    {
        return;
    }
    QVariantMap msg;
    msg.insert("path","/DroneCollectionModel");
    QJsonDocument doc(QJsonObject::fromVariantMap(msg));
    Message m(doc.toBinaryData(), QDateTime::currentDateTime(), tr("получить дроны"), this->name(),
              "DroneCollectionModel", Message::Format::Json);
    send(m);
    Q_ASSERT(_webSocket);
    _webSocket->sendTextMessage(doc.toJson());
    QTimer::singleShot(1000, this, SLOT(getDrones()));
}

void FortisConnection::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QVariantMap msg = doc.object().toVariantMap();
    Message m(doc.toBinaryData(), QDateTime::currentDateTime(), "", msg["path"].toString()
            ,this->name(), Message::Format::Json);
    receive(m);
    if (msg["response"] == "DronesList")
    {
        _isDronesReceived = true;
        foreach (auto droneNum, msg["message"].toMap()["drones"].toList())
        {
            if (!_drones.contains(droneNum.toInt()))
            {
                _drones << droneNum.toInt();
                _lastReceivedTime[droneNum.toInt()] = QTime::currentTime();
            }
        }
        qDebug() << "Drones:" << _drones;
        subscribeToPingMicroservices();
    }

    else if (msg["response"] == "droneping")
    {
        auto map = msg["message"].toMap();
        int droneNumber;
        if (map.contains("dronenumber"))
        {
            droneNumber = map.value("dronenumber").toInt();
        }
        else
        {
            return;
        }
        bool ping;
        if (map.contains("ping"))
        {
            ping = map.value("ping").toBool();
        }
        else
        {
            return;
        }
        QString caption;
        if (map.contains("dronecaption"))
        {
            caption = map.value("dronecaption").toString();
        }
        if (ping)
        {
            qDebug() << "Received ping from" << droneNumber << caption;
            _lastReceivedTime[droneNumber] = QTime::currentTime();
        }
    }
}

void FortisConnection::subscribeToPingMicroservices()
{
    if (_webSocket == nullptr)
    {
        return;
    }

    foreach (int droneNum, _drones)
    {
        QVariantMap msg;
        msg.insert("path","/DroneCollectionModel/" + QString::number(droneNum) + "/DronePing");
        msg.insert("command","subscribe");
        QVariantMap message;
        message.insert("servicepath","/GlobalCommander");
        message.insert("clientname","FortisConnection");
        message.insert("clienttype",1);
        QVariantMap subscriptionLevel;
        subscriptionLevel.insert("level",1);
        subscriptionLevel.insert("param",0);
        message.insert("subscriptionLevel",subscriptionLevel);
        msg.insert("message",message);
        QJsonDocument doc(QJsonObject::fromVariantMap(msg));
        _webSocket->sendTextMessage(doc.toJson());
        Message m(doc.toBinaryData(), QDateTime::currentDateTime(), "", this->name(),
                  "/DroneCollectionModel/" + QString::number(droneNum) + "/DronePing", Message::Format::Json);
        send(m);
    }
}

void FortisConnection::checkState()
{
    QTimer::singleShot(CHECK_STATE_TIME_INTERVAL_MSEC, this, SLOT(checkState()));

    QHash<int, bool> drones;

    QTime currTime = QTime::currentTime();
    for (auto it = _lastReceivedTime.constBegin(); it != _lastReceivedTime.constEnd(); ++it)
    {
        int msec_diff = currTime.msecsSinceStartOfDay() - it.value().msecsSinceStartOfDay();
        if (msec_diff < CHECK_STATE_TIME_INTERVAL_MSEC)
        {
            qDebug() << "Drone" << it.key() << "connection test passed";
        }
        else
        {
            qDebug() << "Drone" << it.key() << "connection test failed";
        }
        drones.insert(it.key(), msec_diff < CHECK_STATE_TIME_INTERVAL_MSEC);
    }
    emit statusReceived(drones);

    if (_isConnected)
    {
        emit connected();
    }
    else
    {
        emit disconnected();
    }
}

void FortisConnection::forcePing()
{
    QTimer::singleShot(FORCE_PING_TIME_INTERVAL_MSEC, this, SLOT(forcePing()));

    if (!_isConnected || !_isDronesReceived)
    {
        return;
    }

    if (_webSocket == nullptr)
    {
        return;
    }

    for (auto it = _lastReceivedTime.constBegin(); it != _lastReceivedTime.constEnd(); ++it)
    {
        qDebug() << "Drone" << it.key() << "force ping sended";
        QVariantMap msg;
        msg.insert("path","/DroneCollectionModel/" + QString::number(it.key()) + "/DronePing");
        QJsonDocument doc(QJsonObject::fromVariantMap(msg));
        //Should be done twice because of Fortis ping implementation...
        //look in DeviceListenerV3::SendCommand() -> case DeviceListenerCommands::Ping
        Q_ASSERT(_webSocket);
        _webSocket->sendTextMessage(doc.toJson());
        _webSocket->sendTextMessage(doc.toJson());
        Message m(doc.toBinaryData(), QDateTime::currentDateTime(), "", this->name(),
                  "/DroneCollectionModel/" + QString::number(it.key()) + "/DronePing", Message::Format::Json);
        send(m);
        send(m);
    }
}
