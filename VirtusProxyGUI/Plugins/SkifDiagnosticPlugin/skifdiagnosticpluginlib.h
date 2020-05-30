#ifndef SKIFDIAGNOSTICPLUGINLIB_H
#define SKIFDIAGNOSTICPLUGINLIB_H

#include "pluginiface.h"
#include <QIcon>
#include <QString>

class SkifDiagnosticPlugin: public PluginIFace
{
    Q_OBJECT
public:
    SkifDiagnosticPlugin(QString _name, QString _version, QIcon _icon);
    // PluginIFace interface
public:
    void start();
};
#endif // SKIFDIAGNOSTICPLUGINLIB_H
