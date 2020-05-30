#ifndef SKIFDIAGNOSTICPLUGIN_H
#define SKIFDIAGNOSTICPLUGIN_H

#include "skifdiagnosticpluginlib_global.h"
#include "pluginiface.h"

extern "C" SKIFDIAGNOSTICPLUGIN_EXPORT PluginIFace *create();
extern "C" SKIFDIAGNOSTICPLUGIN_EXPORT void deletePlugin(PluginIFace* plugin);
#endif // SKIFDIAGNOSTICPLUGIN_H
