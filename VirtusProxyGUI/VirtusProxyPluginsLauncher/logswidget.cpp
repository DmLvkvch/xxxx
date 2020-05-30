#include "logswidget.h"
#include "message.h"
#include <QGridLayout>
#include <QPainter>
#include <QSizePolicy>
#include <QStyleOption>
#include <QHeaderView>
#include <QString>
#include <QResizeEvent>


LogsWidget::LogsWidget(Logs* logs)
{
    this->setWindowTitle("Сообщения");
    this->logs = logs;
    init();
}
LogsWidget::~LogsWidget()
{

}
void LogsWidget::init()
{
    grid = new QGridLayout(this);
    setLayout(grid);
    QHeaderView* header;
    this->table = new QTableWidget(this);
    this->table->setMinimumSize(this->width(), this->height());
    this->table->setColumnCount(8);
    this->table->setHorizontalHeaderLabels(QStringList()<<tr("Время")<<tr("Отправитель")<<tr("Получатель")
                                           <<tr("Статус")<<tr("Приоритет")<<"id"<<tr("Данные")<<tr("Формат"));
    grid->addWidget(this->table, 0, 0);
    header = this->table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Interactive);
    header->setSectionResizeMode(QHeaderView::Stretch);
    this->table->setRowCount(this->logs->size());
    fillTable();
}

void LogsWidget::fillTable(){
    for (int i = 0;i<logs->size();i++)
    {
        this->table->setItem(i, 0, new QTableWidgetItem(logs->message(i).date().toString()));
        this->table->setItem(i, 1, new QTableWidgetItem(logs->message(i).sender()));
        this->table->setItem(i, 2, new QTableWidgetItem(logs->message(i).receiver()));
        this->table->setItem(i, 3, new QTableWidgetItem(logs->message(i).status()));
        this->table->setItem(i, 4, new QTableWidgetItem(logs->message(i).priority()));
        this->table->setItem(i, 5, new QTableWidgetItem(QString::number(logs->message(i).id())));
        this->table->setItem(i, 7, new QTableWidgetItem(Message::formatToString(logs->message(i).format())));
    }
}

void LogsWidget::resizeEvent(QResizeEvent *event)
{

}

void LogsWidget::paintEvent(QPaintEvent * e)
{

}
