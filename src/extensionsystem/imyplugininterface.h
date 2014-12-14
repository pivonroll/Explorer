#ifndef IMyPluginInterface_H
#define IMyPluginInterface_H

#include "extensionsystem_global.h"
#include <QtPlugin>

class EXTENSIONSYSTEM_EXPORT IPlugin : public QObject
{
    Q_OBJECT

public:
    IPlugin();
    virtual ~IPlugin();
    virtual void initialize() = 0;
    virtual void uninitialize() = 0;
};

#endif // IMyPluginInterface_H

