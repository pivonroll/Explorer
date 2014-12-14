include(../plugin.pri)

QT += widgets

DEFINES += DIRECTORYVIEW_LIBRARY

TEMPLATE = lib
TARGET = $$qtLibraryTarget(directoryview)

DESTDIR = $$PLUGIN_PATH

INCLUDEPATH += ../../extensionsystem

HEADERS += \
    directoryview.h \
	directoryview_global.h \
    directoryviewwidget.h \
    layouts/directorygridlayout.h \
    directoryview_constants.h \
    inodeitemwidget.h \
    common.h

SOURCES += \
    directoryview.cpp \
    directoryviewwidget.cpp \
    layouts/directorygridlayout.cpp \
    inodeitemwidget.cpp
    
OTHER_FILES += \
	directoryview.json

RESOURCES += \
    resource.qrc

