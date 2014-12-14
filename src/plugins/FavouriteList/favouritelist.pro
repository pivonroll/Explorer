include(../plugin.pri)

QT += widgets

DEFINES += FAVOURITELIST_LIBRARY

TEMPLATE = lib
TARGET = $$qtLibraryTarget(favouritelist)

DESTDIR = $$PLUGIN_PATH

INCLUDEPATH += ../../extensionsystem

HEADERS += \
    favouritelist.h \
	favouritelist_global.h \
    favouritelistwidget.h

SOURCES += \
    favouritelist.cpp \
    favouritelistwidget.cpp
    
OTHER_FILES += \
	favouritelist.json

FORMS += \
    favouritelistwidget.ui

