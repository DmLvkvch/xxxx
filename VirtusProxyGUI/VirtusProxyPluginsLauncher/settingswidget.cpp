
#include "settingswidget.h"
#include "settingsitem.h"
#include "connectioniface.h"
#include "setting.h"
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QSpinBox>
#include <QStyleOption>
#include <QVBoxLayout>
#include <iostream>


SettingsWidget::SettingsWidget(QList<QSharedPointer<ConnectionIFace>> & ifaces): QWidget(nullptr)
{
    this->_ifaces = ifaces;
    this->setWindowTitle(QString::fromLocal8Bit(tr("Настройки").toLocal8Bit().data()));
    _saveButton = QSharedPointer<QPushButton>( new QPushButton());
    _saveButton->setText(QString::fromLocal8Bit(tr("Сохранить").toLocal8Bit().data()));
    _layout = QSharedPointer<QVBoxLayout>(new QVBoxLayout());
    _buttonsLayout = QSharedPointer<QHBoxLayout>(new QHBoxLayout());
    setLayout(_layout.data());
    _buttonsLayout->addWidget(_saveButton.data());
    init();
    _layout->addLayout(_buttonsLayout.data());
}

SettingsWidget::~SettingsWidget()
{

}

void SettingsWidget::init()
{
    foreach (auto &iface, _ifaces)
    {
        QVBoxLayout* vbl = new QVBoxLayout;
        QLabel* name = new QLabel;
        name->setText(iface->name());
        vbl->addWidget(name);
        foreach (auto& setting, iface->settings())
        {
            vbl->addWidget(new Setting(setting, this));
        }
         _layout->addLayout(vbl);
    }
}

void SettingsWidget::paintEvent(QPaintEvent* e)
{
    QWidget::paintEvent(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.drawRoundedRect(0,5,width()-5, height()-7,3,3);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SettingsWidget::saveSettings()
{

}
