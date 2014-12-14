include($$PWD/../plugin.pri)
include($$PWD/utils/utils.pri)

QT += core widgets

DEFINES += CORE_LIBRARY

TEMPLATE = lib
TARGET = $$qtLibraryTarget(core)

DESTDIR = $$PLUGIN_PATH

INCLUDEPATH += ../../extensionsystem

HEADERS += \
    core.h \
	core_global.h \
    mainwindow.h

SOURCES += \
    core.cpp \
    mainwindow.cpp
    
OTHER_FILES += \
	core.json \

FORMS += \
    mainwindow.ui

include($$PWD/linking.pri)
