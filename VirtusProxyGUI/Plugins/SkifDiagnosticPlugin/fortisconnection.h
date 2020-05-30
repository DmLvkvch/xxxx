#ifndef FORTISCONNECTION_H
#define FORTISCONNECTION_H

#include "connectioniface.h"
class SettingsItem;
#include <QWebSocket>
#include <QUrl>

class FortisConnection:public ConnectionIFace
{
    Q_OBJECT
public:
    FortisConnection(QUrl url);
    ~FortisConnection();
    void connect();
    void send(const Message &message);
    void receive(const Message &message);
signals:
    void statusReceived(QHash<int, bool> drones);
    void connected();
    void disconnected();
private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void reconnect();
    void getDrones();
    void checkState();
    void forcePing();
private:
    QList<int> _drones;
    QWebSocket* _webSocket;
    QUrl _url;
    QHash<int, QTime> _lastReceivedTime;

    bool _isConnected = false;
    bool _isDronesReceived = false;
    void subscribeToPingMicroservices();
};

#endif // FORTISCONNECTION_H
