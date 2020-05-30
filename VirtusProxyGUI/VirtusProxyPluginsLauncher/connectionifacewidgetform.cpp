#include "connectionifacewidgetform.h"
#include "ui_connectionifacewidgetform.h"
#include "connectioniface.h"
#include <QPainter>
#include <QStyleOption>
ConnectionIFaceWidgetForm::ConnectionIFaceWidgetForm(ConnectionIFace &iface, QWidget *parent) :
    QWidget(parent),
    _iface(iface),
    ui(new Ui::ConnectionIFaceWidgetForm)
{
    ui->setupUi(this);
    ui->_ifaceName->setText(QString::fromLocal8Bit(_iface.name().toLocal8Bit().data()));
    ui->_receivedNumber->setText(QString::number(_countIn));
    ui->_sendedNumber->setText(QString::number(_countOut));
    initIFace();
    QObject::connect(&iface, &ConnectionIFace::connectionStatusChanged, this, &ConnectionIFaceWidgetForm::connection);
    QObject::connect(&iface, &ConnectionIFace::messageSended, this, &ConnectionIFaceWidgetForm::msgOut);
    QObject::connect(&iface, &ConnectionIFace::messageReceived, this, &ConnectionIFaceWidgetForm::msgIn);
}

void ConnectionIFaceWidgetForm::initIFace()
{
    ui->_icon->setPixmap(_iface.icon().pixmap(20, 20));
    connection();
}

void ConnectionIFaceWidgetForm::connection()
{
    if(_iface.status()==ConnectionIFace::Status::Connected)
    {
        ui->_connectionStatus->setPixmap(QPixmap(":images/img/circle_green_16_ns.png"));
    }
    else if(_iface.status()==ConnectionIFace::Status::Disconnected)
    {
        ui->_connectionStatus->setPixmap(QPixmap(":images/img/circle_red_16_ns.png"));
    }
    else
    {
        ui->_connectionStatus->setPixmap(QPixmap(":images/img/circle_grey_16_ns.png"));
    }
    update();
}
void ConnectionIFaceWidgetForm::msgIn()
{
    this->_countIn++;
    ui->_receivedNumber->setText(QString::number(this->_countIn));
    update();
}

void ConnectionIFaceWidgetForm::msgOut()
{
    this->_countOut++;
    ui->_sendedNumber->setText(QString::number(this->_countOut));
    update();
}

ConnectionIFaceWidgetForm::~ConnectionIFaceWidgetForm()
{
    delete ui;
}
