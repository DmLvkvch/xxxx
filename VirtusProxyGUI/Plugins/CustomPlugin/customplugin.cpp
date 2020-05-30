#include "customplugin.h"
#include "custompluginlib.h"

PluginIFace *create(){
    PluginIFace* dllPlugin = new Pluginlib("pluginlib", "alpha", QIcon());
    return dllPlugin;
}
