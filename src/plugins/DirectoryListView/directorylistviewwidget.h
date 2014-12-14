#ifndef DIRECTORYLISTVIEW_DIRECTORYLISTVIEWWIDGET_H
#define DIRECTORYLISTVIEW_DIRECTORYLISTVIEWWIDGET_H

#include <QWidget>
#include <QFileInfoList>

#include "directorylistview_global.h"

QT_BEGIN_NAMESPACE
class QListWidgetItem;
class QFileInfo;
class QMenu;
QT_END_NAMESPACE

namespace DirectoryListView {

namespace Ui {
class DirectoryListViewWidget;
}

class DIRECTORYLISTVIEWWIDGETSHARED_EXPORT DirectoryListViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DirectoryListViewWidget(QWidget *parent = 0);
    ~DirectoryListViewWidget();

    QString currentPath() const;
    void setPath(const QString &canonicalPath = QString());

    QStringList selectedInodes() const;
    QStringList selectedInodeCanonicalPaths() const;
    void selectInodes(const QStringList &inodeNames);
    void selectInodesByCanonicalPath(const QStringList &inodeCanonicalPath);

    QAction *addInodeContextMenuAction(const QString &text);
    QAction *addInodeContextMenuAction(const QIcon &icon, const QString &text);

    QAction *addNoSelectedInodeContextMenuAction(const QString &text);
    QAction *addNoSelectedInodeContextMenuAction(const QIcon &icon, const QString &text);

signals:
    void currentDirPathChanged(const QString canonicalPath);

private slots:
    void onItemDoubleClicked(QListWidgetItem *item);
    void onUpButtonClicked();
    void onListWidgetContextMenuRequested(QPoint point);

private:
    void deselectInodes();
    void listRoot();
    void readPath(const QString &path);
    void updateListView(const QFileInfoList &inodeInfoList);
    QListWidgetItem *createItemForInode(const QFileInfo &inodeInfo) const;

    void setPathInNodeItem(QListWidgetItem *item, const QString &path) const;
    QString readPathFromNodeItem(const QListWidgetItem *item) const;

    void showInodeContextMenu(QPoint point);
    void showNonSelectionContextMenu(QPoint point);

    Ui::DirectoryListViewWidget *ui;
    QString m_currentPath;

    QMenu *m_inodeContextMenu;
    QMenu *m_noSelectedInodeContextMenu;
};


} // namespace DirectoryListView
#endif // DIRECTORYLISTVIEW_DIRECTORYLISTVIEWWIDGET_H
