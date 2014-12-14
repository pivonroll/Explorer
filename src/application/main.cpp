#include <QApplication>
#include <pluginmanager.h>
#include <QDebug>

#include <QMenu>

#include "../plugins/DirectoryListView/directorylistviewwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString pluginPath = QApplication::applicationDirPath() + "/../plugins";
    qDebug() << pluginPath;
    PluginManager::setPluginPath(pluginPath);
    PluginManager::loadPlugins();

    DirectoryListView::DirectoryListViewWidget widget;

    widget.addInodeContextMenuAction("rade");
    widget.addInodeContextMenuAction("buca");

    widget.addNoSelectedInodeContextMenuAction("rade2");
    widget.addNoSelectedInodeContextMenuAction("buca2");

    widget.show();

    return a.exec();
}

