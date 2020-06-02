#ifndef LOGSWIDGETFORM_H
#define LOGSWIDGETFORM_H

#include <QWidget>

namespace Ui {
class LogsWidgetForm;
}
#include "message.h"
class LogsWidgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit LogsWidgetForm(const QList<Message> & _logs, QWidget *parent = nullptr);
    ~LogsWidgetForm();
    void resizeEvent(QResizeEvent *event);
public slots:
    void appendRow(Message message);///<добавление строки в конец таблицы
private:
    QString getLogsColumnName(const int& index);///<имя колонки по индексу
    QStringList getLogsTableHeader();///<список колонок
    int getLogsTableColumnIndex(const QString& name);///<индекс колонки по названию
    void fillTable();
    const QList<Message> & _logs;
    enum class LogsColumns : int
    {
        Id,
        Sender,
        Receiver,
        Date,
        Status,
        Priority,
        Format,
        Caption,
        Description,
        Data,
        ColumnsNum
    };
    Ui::LogsWidgetForm *ui;
};

#endif // LOGSWIDGETFORM_H
