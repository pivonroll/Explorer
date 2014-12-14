#include "directorygridlayout.h"

#include "../directoryview_constants.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDir>

DirectoryGridLayout::DirectoryGridLayout(QObject *parent) :
    QObject(parent)
{
}

DirectoryGridLayout::~DirectoryGridLayout()
{
}

void DirectoryGridLayout::update(QGraphicsView *view, QGraphicsScene *scene, const QString &canonicalDirPath)
{
    if (!view || !scene)
        return;

    QFileInfo dirInfo(canonicalDirPath);
    if (!dirInfo.isDir())
        return;

    scene->clear();

    QRect viewRect = view->contentsRect();
    QDir directory(canonicalDirPath);
    QFileInfoList entryList = directory.entryInfoList(QDir::NoFilter, QDir::DirsFirst);

    foreach (const QFileInfo& entry, entryList) {

    }
}

bool DirectoryGridLayout::checkAllEntriesHaveRepresentingItem(QGraphicsScene *scene, const QFileInfoList &entryList) const
{
    QList<QGraphicsItem *> itemList = scene->items();

    return false;
}
