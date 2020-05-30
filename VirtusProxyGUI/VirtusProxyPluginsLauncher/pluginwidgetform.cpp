#include "pluginwidgetform.h"
#include "ui_pluginwidgetform.h"
#include "pluginiface.h"
#include "connectioniface.h"
#include "connectionifacewidgetform.h"
#include "settingswidget.h"
#include "logswidgetform.h"
#include <QPainter>
#include <QStyleOption>

PluginWidgetForm::PluginWidgetForm(PluginIFace* plugin, QWidget *parent) :
    QWidget(parent), _plugin(plugin),
    ui(new Ui::PluginWidgetForm)
{
    ui->setupUi(this);
    ui->_pluginIcon->setPixmap(QPixmap(this->_plugin->icon().pixmap(20, 20)));
    ui->_pluginName->setText(this->_plugin->name());
    ui->_pluginVersion->setText(this->_plugin->version());
    foreach(auto& iface, this->_plugin->connectedIFaces())
    {
        ui->_connectionIFacesLayout->addWidget(new ConnectionIFaceWidgetForm(*iface));
    }
    handleStart();
}

void PluginWidgetForm::handleStart()
{
    this->_plugin->start();
}

void PluginWidgetForm::initIFaces()
{

}

void PluginWidgetForm::paintEvent(QPaintEvent * e)
{
    QWidget::paintEvent(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    p.drawRoundedRect(0,5,width()-5, height()-7,3,3);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

PluginWidgetForm::~PluginWidgetForm()
{
    delete ui;

}

void PluginWidgetForm::on__messages_clicked()
{
    LogsWidgetForm* l = new LogsWidgetForm(_plugin->messageList());
    QObject::connect(_plugin, &PluginIFace::received, l, &LogsWidgetForm::appendRow);
    QObject::connect(_plugin, &PluginIFace::sended, l, &LogsWidgetForm::appendRow);
    l->show();
}

void PluginWidgetForm::on__settings_clicked()
{
    SettingsWidget* s = new SettingsWidget(this->_plugin->connectedIFaces());
    s->show();
}
