#include "logswidgetform.h"
#include "ui_logswidgetform.h"
#include <QDebug>
#include "message.h"

LogsWidgetForm::LogsWidgetForm(const QList<Message> & logs, QWidget *parent) :
    QWidget(parent), _logs(logs),
    ui(new Ui::LogsWidgetForm)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Сообщения"));
    this->ui->logsTable->setColumnCount(static_cast<int>(LogsColumns::ColumnsNum));
    this->ui->logsTable->setHorizontalHeaderLabels(getLogsTableHeader());
    QHeaderView *header = this->ui->logsTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Interactive);
    fillTable();
}

LogsWidgetForm::~LogsWidgetForm()
{
    delete ui;
}

void LogsWidgetForm::fillTable()
{

    foreach(auto& message, this->_logs)
    {
        appendRow(message);
    }
}

void LogsWidgetForm::appendRow(Message message)
{
    this->ui->logsTable->insertRow(this->ui->logsTable->rowCount());
    for (int i = 0; i < int(LogsColumns::ColumnsNum); ++i)
    {
        QString item;
        LogsColumns column = static_cast<LogsColumns>(i);
        switch (column)
        {
        case LogsColumns::Id:
            item = QString::number(message.id());
            break;
        case LogsColumns::Date:
            item = message.date().toString();
            break;
        case LogsColumns::Sender:
            item = message.sender();
            break;
        case LogsColumns::Receiver:
            item = message.receiver();
            break;
        case LogsColumns::Status:
            item = message.status();
            break;
        case LogsColumns::Caption:
            item = message.caption();
            break;
        case LogsColumns::Description:
            item = message.description();
            break;
        case LogsColumns::Priority:
            item = message.priority();
            break;
        case LogsColumns::Format:
            item = Message::formatToString(message.format());
            break;
        case LogsColumns::Data:
            item = QString::fromStdString(message.data().toStdString());
            break;
        default:
            break;
        }
        this->ui->logsTable->setItem(this->ui->logsTable->rowCount()-1, i, new QTableWidgetItem(item));
    }
}


QStringList LogsWidgetForm::getLogsTableHeader()
{
    QStringList list;
    for (int i = 0; i < int(LogsColumns::ColumnsNum); ++i)
    {
        list << getLogsColumnName(i);
    }
    return list;
}

int LogsWidgetForm::getLogsTableColumnIndex(const QString& name)
{
    auto header = getLogsTableHeader();
    for (int i = 0; i < header.size(); ++i)
    {
        if (name == header.at(i))
        {
            return i;
        }
    }
    return -1;
}

void LogsWidgetForm::resizeEvent(QResizeEvent *event)
{

}

QString LogsWidgetForm::getLogsColumnName(const int& index)
{
    switch (static_cast<LogsColumns>(index))
        {
        case LogsColumns::Id:
            return QObject::tr("Идентификатор");
        case LogsColumns::Date:
            return QObject::tr("Время");
        case LogsColumns::Sender:
            return QObject::tr("Отправитель");
        case LogsColumns::Receiver:
            return QObject::tr("Получатель");
        case LogsColumns::Status:
            return QObject::tr("Статус");
        case LogsColumns::Caption:
            return QObject::tr("Заголовок");
        case LogsColumns::Description:
            return QObject::tr("Описание");
        case LogsColumns::Priority:
            return QObject::tr("Приоритет");
        case LogsColumns::Format:
            return QObject::tr("Формат");
        case LogsColumns::Data:
            return QObject::tr("Данные");
        default:
            return "Unknown column index";
        }
}
