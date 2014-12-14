#ifndef DIRECTORYGRIDLAYOUT_H
#define DIRECTORYGRIDLAYOUT_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QGraphicsView;
class QFileInfo;
typedef QList<QFileInfo> QFileInfoList;
QT_END_NAMESPACE

class DirectoryGridLayout : public QObject
{
    Q_OBJECT
public:
    explicit DirectoryGridLayout(QObject *parent = 0);
    ~DirectoryGridLayout();

    void update(QGraphicsView *view, QGraphicsScene *scene, const QString &canonicalDirPath);

private:
    bool checkAllEntriesHaveRepresentingItem(QGraphicsScene *scene, const QFileInfoList &entryList) const;
};

#endif // DIRECTORYGRIDLAYOUT_H
