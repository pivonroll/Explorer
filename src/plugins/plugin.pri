include(../extensionsystem/extensionsystem.pri)
CONFIG += plugin
CONFIG += shared dll

unix:!macx {
   QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN
   QMAKE_LFLAGS += -Wl,--rpath=\\\$\$ORIGIN/../lib
}


