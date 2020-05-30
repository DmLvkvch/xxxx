#include "settingsitem.h"

SettingsItem::SettingsItem()
{
    this->max = 1;
    this->min = 0;
    this->name = "IP";
    this->step = 1;
    this->type = Type::Unknown;
    this->value = "0.0.0.0";
    this->precision = 0;
}

SettingsItem::SettingsItem(QString name,QVariant value,  Type type, double min, double max, double step, int precision):
    name(name),value(value), type(type), min(min), max(max), step(step), precision(precision)
{

}

