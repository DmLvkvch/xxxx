#include "skifdiagnosticpluginlib.h"
#include <QDebug>
#include "connectioniface.h"
#include "fortisconnection.h"
#include "skifconnection.h"
#include <QUrl>

SkifDiagnosticPlugin::SkifDiagnosticPlugin(QString _name, QString _version, QIcon _icon):PluginIFace(_name, _version, _icon)
{
    QUrl url("ws://127.0.0.1:12302");
    ConnectionIFace* iface = new FortisConnection(url);
    this->addConnectionIFace(iface);
    ConnectionIFace* iface2 = new SkifConnection();
    this->addConnectionIFace(iface2);
}

void SkifDiagnosticPlugin::start()
{
    foreach(auto& iface, this->_connectedIFaces)
    {
        iface->connect();
    }
}


