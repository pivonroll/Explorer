include(../config.pri)

TEMPLATE = lib
TARGET = ExtensionSystem
CONFIG += shared dll
DEFINES += EXTENSIONSYSTEM_LIBRARY

HEADERS += \
    extensionsystem_global.h \
    pluginmanager.h \
    imyplugininterface.h

SOURCES += \
    pluginmanager.cpp \
    imyplugininterface.cpp

DESTDIR = $$LIBRARY_PATH

