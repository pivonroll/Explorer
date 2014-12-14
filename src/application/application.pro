 
#-------------------------------------------------
#
# Project created by QtCreator 2013-02-20T20:53:56
#
#-------------------------------------------------
include(../extensionsystem/extensionsystem.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Explorer
TEMPLATE = app

SOURCES += \
		  main.cpp

DESTDIR = $$BINARY_PATH

unix:!macx{
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/..
    QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../lib
}

include(linking.pri)
