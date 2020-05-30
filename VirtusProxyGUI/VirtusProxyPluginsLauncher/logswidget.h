#ifndef LOGSWIDGET_H
#define LOGSWIDGET_H

#include "connectioniface.h"
#include "logs.h"
#include <QGridLayout>
#include <QTableWidget>
#include <QWidget>
/*!
 *  class-widget displaying list of messages
 */

class LogsWidget: public QWidget
{
    Q_OBJECT
public:
    LogsWidget(Logs* logs);
    void paintEvent(QPaintEvent * e);
   ~LogsWidget();
    enum class LogsColumns : int
    {
        Id,
        Status,
        Priority,
        Data,
        Date,
        Format,
        Caption,
        Description,
        Receiver,
        Sender,
        ColumnsNum
    };
    void resizeEvent(QResizeEvent *event);
private:
    void init();
    void fillTable();
    QGridLayout*  grid;
   // QList<Message> listOfMessages;
    Logs* logs;
    QTableWidget* table;
};

#endif // LOGSWIDGET_H
