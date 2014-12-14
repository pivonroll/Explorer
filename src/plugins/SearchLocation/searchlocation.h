#ifndef SEARCHLOCATION_H
#define SEARCHLOCATION_H

#include <QObject>
#include <imyplugininterface.h>

class SearchLocation : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugin.based.app" FILE "searchlocation.json")

public:
    explicit SearchLocation();
    ~SearchLocation();

    void initialize();
    void uninitialize();
};

#endif // FIRSTPLUGIN_H

