include(../plugin.pri)

DEFINES += SEARCHLOCATION_LIBRARY

TEMPLATE = lib
TARGET = $$qtLibraryTarget(searchlocation)

DESTDIR = $$PLUGIN_PATH

INCLUDEPATH += ../../extensionsystem

HEADERS += \
    searchlocation.h \
	searchlocation_global.h

SOURCES += \
    searchlocation.cpp
    
OTHER_FILES += \
	searchlocation.json

