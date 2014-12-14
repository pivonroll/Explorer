TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += \
	extensionsystem_lib \
    plugins_shared \
	application_bin \


extensionsystem_lib.subdir = src/extensionsystem

plugins_shared.subdir = src/plugins
plugins_shared.depends = extensionsystem_lib

application_bin.subdir = src/application
application_bin.depends += extensionsystem_lib
application_bin.depends += plugins_shared

