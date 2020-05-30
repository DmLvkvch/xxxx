TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
    CommonInterfaces \
    Plugins \
    VirtusProxyPluginsLauncher
	
Plugins.depends = CommonInterfaces
VirtusProxyPluginsLauncher.depends = CommonInterfaces Plugins
