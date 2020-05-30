#include "skifconnection.h"
#include "settingsitem.h"
SkifConnection::SkifConnection():ConnectionIFace(tr("Скиф"), QList<SettingsItem>())
{
    setIconPath(":/images/res/skif_logo.png");
}

void SkifConnection::send(const Message &message)
{

}

void SkifConnection::receive(const Message &message)
{

}

void SkifConnection::connect()
{

}
