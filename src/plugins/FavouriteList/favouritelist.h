#ifndef FAVOURITELIST_H
#define FAVOURITELIST_H

#include <QObject>
#include <imyplugininterface.h>

class FavouriteList : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugin.based.app" FILE "favouritelist.json")

public:
    explicit FavouriteList();
    ~FavouriteList();

    void initialize();
    void uninitialize();
};

#endif // FIRSTPLUGIN_H

