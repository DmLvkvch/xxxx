#include "connectionifacewidget.h"
#include "connectioniface.h"

#include <QLabel>
#include <QPainter>
#include <QString>
#include <QString>
#include <QStyleOption>
#include <QDebug>
ConnectionIFaceWidget::ConnectionIFaceWidget(ConnectionIFace & iface):_iface(iface)
{
    setLayout(&_layout);
    initIFace();
    QObject::connect(&iface, &ConnectionIFace::connectionStatusChanged, this, &ConnectionIFaceWidget::connection);
    QObject::connect(&iface, &ConnectionIFace::messageSended, this, &ConnectionIFaceWidget::msgOut);
    QObject::connect(&iface, &ConnectionIFace::messageReceived, this, &ConnectionIFaceWidget::msgIn);
}


void ConnectionIFaceWidget::initIFace()
{
        QHBoxLayout *hl = new QHBoxLayout;
        QLabel* icon = new QLabel;
        QPixmap pixmap = _iface.icon().pixmap(20, 20);
        icon->setPixmap(pixmap);
        hl->addWidget(&_connectionStatus);
        connection();
        hl->addWidget(icon);
        QLabel* name = new QLabel;
        name->setText(QString::fromLocal8Bit(_iface.name().toLocal8Bit().data()));
        hl->addWidget(name);
        _messagesIn.setText(QString::fromLocal8Bit(tr("Получено: ").toLocal8Bit().data())+QString::number(this->_countIn));
        hl->addWidget(&_messagesIn);
        _messagesOut.setText(QString::fromLocal8Bit(tr("Отправлено: ").toLocal8Bit().data())+QString::number(this->_countOut));
        hl->addWidget(&_messagesOut);
        _layout.addLayout(hl);
}

void ConnectionIFaceWidget::connection()
{
    if(_iface.status()==ConnectionIFace::Status::Connected)
    {
        _connectionStatus.setPixmap(QPixmap(":images/img/circle_green_16_ns.png"));
    }
    else if(_iface.status()==ConnectionIFace::Status::Disconnected)
    {
        _connectionStatus.setPixmap(QPixmap(":images/img/circle_red_16_ns.png"));
    }
    else
    {
        _connectionStatus.setPixmap(QPixmap(":images/img/circle_grey_16_ns.png"));
    }
    update();
}
void ConnectionIFaceWidget::msgIn()
{
    this->_countIn++;
    _messagesIn.setText(QString::fromLocal8Bit(tr("Получено: ").toLocal8Bit().data())+QString::number(this->_countIn));
    update();
}

void ConnectionIFaceWidget::msgOut()
{
    this->_countOut++;
    _messagesOut.setText(QString::fromLocal8Bit(tr("Отправлено: ").toLocal8Bit().data())+QString::number(this->_countOut));
    update();
}

void ConnectionIFaceWidget::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.drawRoundedRect(0,5,width()-5, height()-7,3,3);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
