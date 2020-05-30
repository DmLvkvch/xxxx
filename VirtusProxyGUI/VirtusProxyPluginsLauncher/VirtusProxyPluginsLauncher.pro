QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


TARGET = VirtusProxyPluginsLauncher

SOURCES += \
    connectionifacewidgetform.cpp \
    logswidgetform.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowsettings.cpp \
    pluginwidgetform.cpp \
    setting.cpp \
    settingswidget.cpp
HEADERS += \
    connectionifacewidgetform.h \
    logswidgetform.h \
    mainwindow.h \
    mainwindowsettings.h \
    pluginwidgetform.h \
    setting.h \
    settingswidget.h

FORMS += \
    connectionifacewidgetform.ui \
    logswidgetform.ui \
    mainwindow.ui \
    mainwindowsettings.ui \
    pluginwidgetform.ui \
    setting.ui

INCLUDEPATH += "../CommonInterfaces/"

CONFIG(debug, debug|release): {
    OUTPUT_DIR = "$$PWD/../buildVirtusProxyPluginsLauncher/debug/"
    COMMONINTERFACES_DIR = "$$PWD/../buildCommonInterfaces/debug/"
    PLUGINS_DIR = "$$PWD/../buildPlugins/debug/"
} else: {
    OUTPUT_DIR = "$$PWD/../buildVirtusProxyPluginsLauncher/release/"
    COMMONINTERFACES_DIR = "$$PWD/../buildCommonInterfaces/release/"
    PLUGINS_DIR = "$$PWD/../buildPlugins/release/"
}

LIBS += -L"$$COMMONINTERFACES_DIR/bin/" -lCommonInterfaces

OBJECTS_DIR = "$$OUTPUT_DIR/obj/"
MOC_DIR = "$$OUTPUT_DIR/moc/"
RCC_DIR = "$$OUTPUT_DIR/res/"
UI_DIR = "$$OUTPUT_DIR/ui/"
DESTDIR = "$$OUTPUT_DIR/bin/"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
