include(../plugin.pri)

QT += widgets

DEFINES += DIRECTORYLISTVIEWWIDGET_LIBRARY

TEMPLATE = lib
TARGET = $$qtLibraryTarget(directorylistview)

DESTDIR = $$PLUGIN_PATH

INCLUDEPATH += ../../extensionsystem

HEADERS += \
    directorylistview.h \
    directorylistview_global.h \
    directorylistviewwidget.h

SOURCES += \
    directorylistview.cpp \
    directorylistviewwidget.cpp
    
OTHER_FILES += \
    directorylistview.json

FORMS += \
    directorylistviewwidget.ui

RESOURCES += \
    resources.qrc

