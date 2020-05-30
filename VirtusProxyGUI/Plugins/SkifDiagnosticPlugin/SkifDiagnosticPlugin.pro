QT += gui network

TARGET = SkifDiagnosticPlugin
TEMPLATE = lib
DEFINES += SKIFDIAGNOSTICPLUGIN_LIBRARY
QT += websockets
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

SOURCES += \
    fortisconnection.cpp \
    skifconnection.cpp \
    skifdiagnosticplugin.cpp \
    skifdiagnosticpluginlib.cpp

HEADERS += \
    fortisconnection.h \
    skifconnection.h \
    skifdiagnosticplugin.h \
    skifdiagnosticpluginlib_global.h \
    skifdiagnosticpluginlib.h

INCLUDEPATH += "../../CommonInterfaces"

CONFIG(debug, debug|release): {
    OUTPUT_DIR = "$$PWD/../../buildPlugins/debug/"
    COMMONINTERFACES_DIR = "$$PWD/../../buildCommonInterfaces/debug/"
} else: {
    OUTPUT_DIR = "$$PWD/../../buildPlugins/release/"
    COMMONINTERFACES_DIR = "$$PWD/../../buildCommonInterfaces/release/"
}

LIBS += -L"$$COMMONINTERFACES_DIR/bin/" -lCommonInterfaces

OBJECTS_DIR = "$$OUTPUT_DIR/obj/"
MOC_DIR = "$$OUTPUT_DIR/moc/"
RCC_DIR = "$$OUTPUT_DIR/res/"
UI_DIR = "$$OUTPUT_DIR/ui/"
DESTDIR = "$$OUTPUT_DIR/bin/"

RESOURCES += \
    resources.qrc
