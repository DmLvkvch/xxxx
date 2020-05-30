#include "skifdiagnosticpluginlib.h"
#include "skifdiagnosticplugin.h"
#include <QDebug>

PluginIFace *create()
{
    PluginIFace* plugin = nullptr;
    QIcon icon(":images/res/MainIcon.ico");
    plugin = new SkifDiagnosticPlugin("СкифДиагностика", "0.0.2", icon);
    qDebug()<<plugin;
    return plugin;
}

void deletePlugin(PluginIFace* plugin)
{
    qDebug()<<"delete";
    qDebug()<<plugin;
    if(plugin==nullptr)
    {
        return;
    }
    delete plugin;
    plugin = nullptr;
}
