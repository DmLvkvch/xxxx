#include "logswidget.h"
#include "pluginwidget.h"
#include "settingswidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QStyleOption>
#include <QDebug>
#include "connectionifacewidget.h"
#include "connectionifacewidgetform.h"
#include "pluginiface.h"
PluginWidget::PluginWidget(PluginIFace* plugin, QWidget* parent):QWidget(parent), _plugin(plugin)
{
    this->_widgetName = plugin->name();
    setLayout(&_grid);
    _openLogsButton.setText(QString::fromLocal8Bit(tr("Сообщения").toLocal8Bit().data()));
    _openSettingsButton.setText(QString::fromLocal8Bit(tr("Настройки").toLocal8Bit().data()));
    _grid.addWidget(&_openLogsButton, 1, 0);
    _grid.addWidget(&_openSettingsButton, 1, 1);
    this->_settings = QSharedPointer<SettingsWidget>(new SettingsWidget(this->_plugin->connectedIFaces()));
    QObject::connect(&_openSettingsButton, &QPushButton::clicked,
            this, &PluginWidget::handleOpenSettings);
    QObject::connect(&_openLogsButton, &QPushButton::clicked, this, &PluginWidget::handleOpenLogs);
    handleStart();
    initIFaces();
}

PluginWidget::~PluginWidget()
{

}

void PluginWidget::handleOpenLogs()
{
    LogsWidget* l = new LogsWidget(new Logs(_plugin->messageList()));
    l->show();
}

void PluginWidget::handleOpenSettings()
{
    this->_settings->show();
}

void PluginWidget::initIFaces()
{
    QVBoxLayout* vb = new QVBoxLayout;
    foreach(auto& iface, this->_plugin->connectedIFaces())
    {
        vb->addWidget(new ConnectionIFaceWidgetForm(*iface));
    }
    _grid.addLayout(vb, 0, 0);
}

void PluginWidget::handleStart()
{
    this->_plugin->start();
}

void PluginWidget::paintEvent(QPaintEvent * e)
{
    QWidget::paintEvent(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.drawRoundedRect(0,5,width()-5, height()-7,3,3);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
