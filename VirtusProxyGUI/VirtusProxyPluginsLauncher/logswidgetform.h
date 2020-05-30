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
    void appendRow(Message message);
private:
    QString getLogsColumnName(const int& index);
    QStringList getLogsTableHeader();
    int getLogsTableColumnIndex(const QString& name);
    void fillTable();
    const QList<Message> & _logs;
    enum class LogsColumns : int
    {
        Id,
        Receiver,
        Sender,
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
