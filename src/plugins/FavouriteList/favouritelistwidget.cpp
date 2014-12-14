#include "favouritelistwidget.h"
#include "ui_favouritelistwidget.h"

#include <QFileInfo>
#include <QMenu>
#include <QListWidgetItem>

FavouriteListWidget::FavouriteListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FavouriteListWidget)
{
    ui->setupUi(this);
    m_locationContextMenu = new QMenu(this);
    ui->m_favouriteListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->m_favouriteListWidget, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(onCustomContextMenuRequested(QPoint)));

    connect(ui->m_favouriteListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(onLocationItemClicked(int)));
}

FavouriteListWidget::~FavouriteListWidget()
{
    delete ui;
}

QAction *FavouriteListWidget::addLocationContextMenuAction(const QString &text)
{
    return m_locationContextMenu->addAction(text);
}

QAction *FavouriteListWidget::addLocationContextMenuAction(const QIcon &icon, const QString &text)
{
    return m_locationContextMenu->addAction(icon, text);
}

void FavouriteListWidget::removeLocationContextMenuAction(QAction *action)
{
    m_locationContextMenu->removeAction(action);
}

void FavouriteListWidget::addLocation(const QString &canonicalPath)
{
    if (isLocationInList(canonicalPath))
        return;

    QFileInfo info(canonicalPath);

    QListWidgetItem *locationItem = 0;

    if (info.isRoot())
        locationItem = new QListWidgetItem(info.canonicalPath());
    else if (info.isDir())
        locationItem = new QListWidgetItem(info.fileName());

    if (locationItem) {
        locationItem->setData(Qt::UserRole, canonicalPath);
        ui->m_favouriteListWidget->addItem(locationItem);
    }
}

int FavouriteListWidget::count() const
{
    return ui->m_favouriteListWidget->count();
}

bool FavouriteListWidget::isLocationInList(const QString &canonicalPath) const
{
    for (int i = 0; i < ui->m_favouriteListWidget->count(); ++i) {
        QListWidgetItem *item = ui->m_favouriteListWidget->item(i);

        if (item && readPathFromNodeItem(item) == canonicalPath) {
            return true;
        }
    }

    return false;
}

QString FavouriteListWidget::location(int index) const
{
    if (0 <= index && index < ui->m_favouriteListWidget->count())
        return readPathFromNodeItem(ui->m_favouriteListWidget->item(index));

    return QString();
}

void FavouriteListWidget::removeLocation(const QString &canonicalPath)
{
    for (int i = 0; i < ui->m_favouriteListWidget->count(); ++i) {
        QListWidgetItem *item = ui->m_favouriteListWidget->item(i);

        if (item && readPathFromNodeItem(item) == canonicalPath) {
            ui->m_favouriteListWidget->removeItemWidget(item);
            return;
        }
    }
}

void FavouriteListWidget::removeAt(int index)
{
    if (0 <= index && index < ui->m_favouriteListWidget->count())
        ui->m_favouriteListWidget->removeItemWidget(ui->m_favouriteListWidget->item(index));
}

void FavouriteListWidget::onCustomContextMenuRequested(QPoint point)
{
    QListWidgetItem *item = ui->m_favouriteListWidget->itemAt(point);

    if (item && m_locationContextMenu)
        m_locationContextMenu->exec(mapToGlobal(point));
}

void FavouriteListWidget::onLocationItemClicked(int row)
{
    if (0 <= row && row < ui->m_favouriteListWidget->count()) {
        QListWidgetItem *item = ui->m_favouriteListWidget->item(row);

        if (item) {
            QString path = readPathFromNodeItem(item);
            if (!path.isEmpty())
                emit locationClicked(path);
        }
    }
}

QString FavouriteListWidget::readPathFromNodeItem(const QListWidgetItem *item) const
{
    if (!item)
        return QString();

    return item->data(Qt::UserRole).toString();
}
