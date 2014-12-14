#ifndef DIRECTORYLISTVIEWWIDGET_H
#define DIRECTORYLISTVIEWWIDGET_H

#include <QObject>
#include <imyplugininterface.h>

class DirectoryListView : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugin.based.app" FILE "directorylistview.json")

public:
    explicit DirectoryListView();
    ~DirectoryListView();

    void initialize();
    void uninitialize();
};

#endif // FIRSTPLUGIN_H

