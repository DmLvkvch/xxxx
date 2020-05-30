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
    unsigned long id() const;///<получить id сообщения
    QString status() const;///<получить статус сообщения
    QString priority() const;///<получить приоритет сообщения
    QByteArray data() const;///<получить данных из сообщения
    QDateTime date() const;///<получить время
    Format format() const;///<получить формат сообщения
    QString caption() const;///<получить заголовок сообщения
    QString description() const;///<получить описание сообщения
    QString receiver() const;///<получить получателя сообщения
    QString sender() const;///<получить отправителя сообщения
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
