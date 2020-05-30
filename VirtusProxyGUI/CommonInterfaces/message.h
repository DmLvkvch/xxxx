#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QList>
#include <QDateTime>
#include "commoninterfaces_global.h"


/*!
 *  class defining message structure
 */
class COMMONINTERFACES_EXPORT Message
{
public:
    enum class Format : int
    {
        Unknown, Bin, Txt, Json, Xml, Rar, Zip
    };
    enum class Status : int
    {
        Unknown, Recieved, Viewed
    };
    enum class Priority : int
    {
        Unknown, Low, Medium, High
    };
    Message();
    Message(QByteArray data, QDateTime time, QString description, QString sender, QString receiver, Format format);
    ~Message();
    unsigned long id() const;///<�������� id ���������
    QString status() const;///<�������� ������ ���������
    QString priority() const;///<�������� ��������� ���������
    QByteArray data() const;///<�������� ������ �� ���������
    QDateTime date() const;///<�������� �����
    Format format() const;///<�������� ������ ���������
    QString caption() const;///<�������� ��������� ���������
    QString description() const;///<�������� �������� ���������
    QString receiver() const;///<�������� ���������� ���������
    QString sender() const;///<�������� ����������� ���������
    static QString formatToString(Format format);
    QString dataToString() const;
private:
    QString _caption;
    QString _description;
    unsigned long _id;
    QString _receiver;
    QString _sender;
    Status _status = Status::Unknown;
    QDateTime _timestamp;
    Priority _priority = Priority::Unknown;
    QString _type;
    QByteArray _data;
    Format _format = Format::Unknown;
};
#endif // MESSAGE_H
