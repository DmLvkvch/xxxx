#ifndef CONNECTIONIFACEWIDGET_H
#define CONNECTIONIFACEWIDGET_H

#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
class ConnectionIFace;
class ConnectionIFaceWidget:public QWidget
{
    Q_OBJECT
public:
    ConnectionIFaceWidget(ConnectionIFace & iface);
    void paintEvent(QPaintEvent *event);
public slots:
    void connection();
    void msgIn();
    void msgOut();
private:
    void initIFace();
    QHBoxLayout _layout;
    ConnectionIFace & _iface;
    QLabel _connectionStatus;
    QLabel _messagesIn;
    QLabel _messagesOut;
    int _countIn = 0;
    int _countOut = 0;
};

#endif // CONNECTIONIFACEWIDGET_H
