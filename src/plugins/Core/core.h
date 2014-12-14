#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <imyplugininterface.h>

class Core : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugin.based.app" FILE "core.json")

public:
    explicit Core();
    ~Core();

    // IPlugin interface
    void initialize();    
    void uninitialize();
};

#endif // FIRSTPLUGIN_H

