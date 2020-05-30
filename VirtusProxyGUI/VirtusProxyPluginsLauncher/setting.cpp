#include "setting.h"
#include "ui_setting.h"

#include "settingsitem.h"

Setting::Setting(SettingsItem setting, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->ui->_name ->setText(setting.name);
    this->ui->_value->setText(setting.value.toString());
}

Setting::~Setting()
{
    delete ui;
}
