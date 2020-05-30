#include "message.h"

Message::Message()
{
    this->_id = rand()%10;
    this->_status = Status::Recieved;
    this->_priority = Priority::High;
    this->_timestamp = QDateTime::currentDateTime();
}

Message::Message(QByteArray data, QDateTime time, QString description, QString sendr, QString receivr, Format form)
{
    this->_data = data;
    this->_timestamp = time;
    this->_description = description;
    this->_sender = sendr;
    this->_receiver = receivr;
    this->_format = form;
}

unsigned long Message::id() const
{
    return _id;
}

QString Message::caption() const
{
    return this->_caption;
}

QString Message::description() const
{
    return this->_description;
}

QByteArray Message::data() const
{
    return this->_data;
}


QString Message::status() const
{
    switch (this->_status) {
    case Status::Recieved:
        return "received";
    case Status::Viewed:
        return "viewed";
    default:
        return "unknown";
    }
    return "";
}

QString Message::dataToString() const
{
    QString value;
    switch (this->_format) {
    case Message::Format::Json:

    case Message::Format::Rar:

    case Message::Format::Bin:

    case Message::Format::Txt:

    case Message::Format::Zip:

    case Message::Format::Xml:

    default:
        return "Unknown";
    }
}

QString Message::formatToString(Format format)
{
    switch (format) {
    case Message::Format::Json:
        return "Json";
    case Message::Format::Rar:
        return "Rar";
    case Message::Format::Bin:
        return "Bin";
    case Message::Format::Txt:
        return "Txt";
    case Message::Format::Zip:
        return "Zip";
    case Message::Format::Xml:
        return "Xml";
    default:
        return "Unknown";
    }
}

QString Message::priority() const{
    switch (this->_priority) {
    case Priority::High:
        return "high";
    case Priority::Medium:
        return "medium";
    case Priority::Low:
        return "low";
    default:
        return "unknown";
    }
    return "";
}

QDateTime Message::date() const{
    return this->_timestamp;
}

Message::Format Message::format() const
{
    return this->_format;
}

QString Message::sender() const
{
    return this->_sender;
}

QString Message::receiver() const
{
    return this->_receiver;
}

Message::~Message()
{

}
