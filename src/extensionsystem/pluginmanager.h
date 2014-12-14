#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QString>
#include "extensionsystem_global.h"

class EXTENSIONSYSTEM_EXPORT PluginManager
{
public:
    PluginManager();
    virtual ~PluginManager();

    static void loadPlugins();
    static void setPluginPath(const QString &path);

private:
    static PluginManager* m_instance;
    QString m_pluginPath;
};

#endif // PLUGINMANAGER_H

