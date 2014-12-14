include(../plugin.pri)

QT += network

DEFINES += NETWORKLOCATIONS_LIBRARY

TEMPLATE = lib
TARGET = $$qtLibraryTarget(networklocations)

DESTDIR = $$PLUGIN_PATH

INCLUDEPATH += ../../extensionsystem

HEADERS += \
    networklocations.h \
	networklocations_global.h \
    networklocationslookup.h \
    networkutils.h \
    networkscanner.h

SOURCES += \
    networklocations.cpp \
    networklocationslookup.cpp \
    networkutils.cpp \
    networkscanner.cpp
    
OTHER_FILES += \
	networklocations.json

