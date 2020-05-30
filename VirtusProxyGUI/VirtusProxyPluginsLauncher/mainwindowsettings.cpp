#include "mainwindowsettings.h"
#include "ui_mainwindowsettings.h"
#include <algorithm>
#include <QString>
#include <QDebug>
MainWindowSettings::MainWindowSettings(int count, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindowSettings)
{
    this->_pluginCount = count;
    ui->setupUi(this);
    initComboBox();
    QObject::connect(ui->comboBox, &QComboBox::currentTextChanged,
                     this, &MainWindowSettings::on__rowComboBox_currentIndexChanged);
    QObject::connect(ui->comboBox, &QComboBox::currentTextChanged,
                     this, &MainWindowSettings::on__rowComboBox_currentIndexChanged);
}

void MainWindowSettings::initComboBox()
{
    int num = this->_pluginCount;
    for (int i = 1;i<=this->_pluginCount;i++) {
//        qDebug()<<i<<' '<<num;
//        num = this->_pluginCount%i==0 ? this->_pluginCount/i : this->_pluginCount/i + this->_pluginCount%i;
//        if(!(num*i >= this->_pluginCount && num*i-this->_pluginCount <= std::min(num, i)))
//            continue;
//        if(num!=i)
        ui->comboBox->addItem(QString::number(num - i+1));
        ui->comboBox_2->addItem(QString::number(i));
    }
}

MainWindowSettings::~MainWindowSettings()
{
    delete ui;
}


void MainWindowSettings::on__save_clicked()
{
    int i = ui->comboBox->currentText().toInt();
    int j = ui->comboBox_2->currentText().toInt();
    emit gridChanged(i, j);

}

void MainWindowSettings::on__rowComboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    int rows = arg1.toInt();
    for (int i = 1;i<=this->_pluginCount;i++) {
        if(rows*i>=this->_pluginCount)
            ui->comboBox_2->addItem(QString::number(i));
    }
}

void MainWindowSettings::on__columnComboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox->clear();
    int cols = arg1.toInt();
    for (int i = 1;i<=this->_pluginCount;i++) {
        if(cols*i>=this->_pluginCount)
            ui->comboBox->addItem(QString::number(i));
    }
}
