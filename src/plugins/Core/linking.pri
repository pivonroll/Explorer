include(../../config.pri)

LIBS += -L$$PLUGIN_PATH

CONFIG(debug, debug | release) {
}

CONFIG(release, debug | release) {
}
