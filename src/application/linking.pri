include(../config.pri)

LIBS += -L$$PLUGIN_PATH

CONFIG(debug, debug | release) {
        LIBS *= -ldirectorylistviewd
}

CONFIG(release, debug | release) {
        LIBS *= -ldirectorylistview
}
