#ifndef PLUGINIFACE_H
#define PLUGINIFACE_H

class ConnectionIFace;
#include "message.h"
#include <QIcon>
#include <QList>
#include <QString>
#include <QObject>
#include "commoninterfaces_global.h"

/*!
 *  class describing plugin
 */
class COMMONINTERFACES_EXPORT PluginIFace: public QObject
{
    Q_OBJECT
public:
    /*!
      * \brief ����������� ������� ������ PluginIFace
      * �������������� ��� ��������� �������
      */
    PluginIFace(QString _name, QString _version, QIcon _icon);
    QString name() const;///<�������� �������
    QList<QSharedPointer<ConnectionIFace>> & connectedIFaces();///<������ ������������ �����������
    QString version() const;///<������ �������
    QList<Message> messageList();///<������ ���������
    QString id();///<id �������
    virtual void start() = 0;///<������ �������
    QIcon icon();///<������ �������
    virtual ~PluginIFace();
protected:
    void addConnectionIFace(ConnectionIFace* iface);///<�������� ����� ���������
    QList<QSharedPointer<ConnectionIFace>> _connectedIFaces;
signals:
    void connectedIFace(QSharedPointer<ConnectionIFace> iface); ///<����������� � ����������� ������ ����������
    void disconnectedIFace(QSharedPointer<ConnectionIFace> iface); ///<����������� �� ���������� ����������
    void received(const Message & message);///<����������� � ��������� ���������
    void sended(const Message & message);///<����������� �� �������� ���������
    void connectionIFaceChanged();
private slots:
    void messageReceived(const Message & message);
    void messageSended(const Message & message);
    void change();
private:
    QString _name;
    QString _version;
    QIcon _icon;
};

#endif // PLUGINIFACE_H
