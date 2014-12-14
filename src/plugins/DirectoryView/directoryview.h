#ifndef DIRECTORYVIEW_H
#define DIRECTORYVIEW_H

#include <QObject>
#include <imyplugininterface.h>

namespace DirectoryViewPlugin
{

class DirectoryView : public IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.plugin.based.app" FILE "directoryview.json")

public:
    explicit DirectoryView();
    ~DirectoryView();

    void initialize();
    void uninitialize();
};

} // namespace DirectoryViewPlugin

#endif // FIRSTPLUGIN_H

