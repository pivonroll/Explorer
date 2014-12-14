#ifndef FAVOURITELISTWIDGET_H
#define FAVOURITELISTWIDGET_H

#include <QWidget>
#include <QString>

#include "favouritelist_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QListWidgetItem;
QT_END_NAMESPACE

namespace Ui {
class FavouriteListWidget;
}

class FAVOURITELISTSHARED_EXPORT FavouriteListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FavouriteListWidget(QWidget *parent = 0);
    ~FavouriteListWidget();

    QAction *addLocationContextMenuAction(const QString &text);
    QAction *addLocationContextMenuAction(const QIcon &icon, const QString &text);

    void removeLocationContextMenuAction(QAction *action);

    void addLocation(const QString &canonicalPath);
    int count() const;
    bool isLocationInList(const QString &canonicalPath) const;
    QString location(int index) const;
    void removeLocation(const QString &canonicalPath);
    void removeAt(int index);

signals:
    void locationClicked(QString locationCanonicalPath);

private slots:
    void onCustomContextMenuRequested(QPoint point);
    void onLocationItemClicked(int row);

private:
    QString readPathFromNodeItem(const QListWidgetItem *item) const;

    Ui::FavouriteListWidget *ui;
    QMenu *m_locationContextMenu;
};

#endif // FAVOURITELISTWIDGET_H
