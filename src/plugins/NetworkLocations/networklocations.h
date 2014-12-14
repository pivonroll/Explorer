#ifndef NETWORKLOCATIONS_H
#define NETWORKLOCATIONS_H

#include <QObject>
#include <imyplugininterface.h>

class NetworkLocations : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugin.based.app" FILE "networklocations.json")

public:
    explicit NetworkLocations();
    ~NetworkLocations();

    void initialize();
    void uninitialize();
};

#endif // FIRSTPLUGIN_H

