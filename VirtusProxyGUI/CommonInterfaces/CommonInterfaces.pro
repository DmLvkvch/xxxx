QT += core
QT += gui
TARGET = CommonInterfaces
TEMPLATE = lib
DEFINES += COMMONINTERFACES_LIBRARY

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
    connectioniface.cpp \
    message.cpp \
    pluginiface.cpp \
    settingsitem.cpp

HEADERS += \
    connectioniface.h \
    message.h \
    pluginiface.h \
    settingsitem.h \
    commoninterfaces_global.h

CONFIG(debug, debug|release): {
    OUTPUT_DIR = "$$PWD/../buildCommonInterfaces/debug/"
} else: {
    OUTPUT_DIR = "$$PWD/../buildCommonInterfaces/release/"
}

OBJECTS_DIR = "$$OUTPUT_DIR/obj/"
MOC_DIR = "$$OUTPUT_DIR/moc/"
RCC_DIR = "$$OUTPUT_DIR/res/"
UI_DIR = "$$OUTPUT_DIR/ui/"
DESTDIR = "$$OUTPUT_DIR/bin/"
