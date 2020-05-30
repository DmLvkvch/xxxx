#ifndef CUSTOMPLUGINPLUGINLIB_H
#define CUSTOMPLUGINPLUGINLIB_H

#include "pluginiface.h"
#include <QIcon>
class Pluginlib: public PluginIFace
{
public:
    Pluginlib(QString _name, QString _version, QIcon _icon);
    // PluginIFace interface
public:
    void start();
};
#endif // CUSTOMPLUGINPLUGINLIB_H
