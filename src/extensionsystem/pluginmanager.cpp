#include "pluginmanager.h"
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

#include "imyplugininterface.h"

PluginManager* PluginManager::m_instance = new PluginManager;

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{
}

void PluginManager::loadPlugins()
{
    QDir pluginsDir = QDir(m_instance->m_pluginPath);

    qDebug() << "Try to load plugins in folder " << pluginsDir.path();

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
#ifdef Q_OS_WIN
        if(fileName.endsWith(".dll")) {
#else
        if(fileName.endsWith(".so")) {
#endif
            qDebug() << "Testing " << pluginsDir.absoluteFilePath(fileName);
            QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin_instance = loader.instance();
            if (plugin_instance) {
                qDebug() << "Loading " << fileName;
                IPlugin *plugin = qobject_cast<IPlugin *>(plugin_instance);
                if(plugin)
                    plugin->initialize();
            }
            else {

                qDebug() << "Error: " << loader.errorString();
            }
        }
    }
}

void PluginManager::setPluginPath(const QString &path)
{
    m_instance->m_pluginPath = path;
}

