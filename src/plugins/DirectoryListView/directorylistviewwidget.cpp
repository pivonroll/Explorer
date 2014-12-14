#include "directorylistviewwidget.h"
#include "ui_directorylistviewwidget.h"

#include <QDir>
#include <QFileInfo>
#include <QMenu>

#include <QDebug>

namespace DirectoryListView {

DirectoryListViewWidget::DirectoryListViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirectoryListViewWidget),
    m_inodeContextMenu(0),
    m_noSelectedInodeContextMenu(0)
{
    ui->setupUi(this);

    ui->m_directoyrListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    m_inodeContextMenu = new QMenu(this);
    m_noSelectedInodeContextMenu = new QMenu(this);

    listRoot();

    connect(ui->m_directoyrListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
    connect(ui->m_goUpButton, SIGNAL(clicked()), this, SLOT(onUpButtonClicked()));

    connect(ui->m_directoyrListWidget, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(onListWidgetContextMenuRequested(QPoint)));
}

DirectoryListViewWidget::~DirectoryListViewWidget()
{
    delete ui;
}

QString DirectoryListViewWidget::currentPath() const
{
    return m_currentPath;
}

void DirectoryListViewWidget::setPath(const QString &canonicalPath)
{
    if (canonicalPath.isEmpty() || !QFileInfo(canonicalPath).exists() || QFileInfo(canonicalPath).isRoot())
        listRoot();

    readPath(canonicalPath);
}

QStringList DirectoryListViewWidget::selectedInodes() const
{
    QStringList paths;
    QList<QListWidgetItem *> selectedInodeItems = ui->m_directoyrListWidget->selectedItems();

    foreach (const QListWidgetItem *inodeItem, selectedInodeItems) {
        if (inodeItem)
            paths << inodeItem->text();
    }

    return paths;
}

QStringList DirectoryListViewWidget::selectedInodeCanonicalPaths() const
{
    QStringList paths;
    QList<QListWidgetItem *> selectedInodeItems = ui->m_directoyrListWidget->selectedItems();

    foreach (const QListWidgetItem *inodeItem, selectedInodeItems) {
        if (inodeItem)
            paths << readPathFromNodeItem(inodeItem);
    }

    return paths;
}

void DirectoryListViewWidget::selectInodes(const QStringList &inodeNames)
{
    deselectInodes();

    for (int i = 0; i < ui->m_directoyrListWidget->count(); ++i) {
        QListWidgetItem *item = ui->m_directoyrListWidget->item(i);
        if (item && inodeNames.contains(item->text()))
            item->setSelected(true);
    }
}

void DirectoryListViewWidget::selectInodesByCanonicalPath(const QStringList &inodeCanonicalPath)
{
    deselectInodes();

    for (int i = 0; i < ui->m_directoyrListWidget->count(); ++i) {
        QListWidgetItem *item = ui->m_directoyrListWidget->item(i);
        if (item && inodeCanonicalPath.contains(readPathFromNodeItem(item)))
            item->setSelected(true);
    }
}

QAction* DirectoryListViewWidget::addInodeContextMenuAction(const QString &text)
{
    return m_inodeContextMenu->addAction(text);
}

QAction *DirectoryListViewWidget::addInodeContextMenuAction(const QIcon &icon, const QString &text)
{
    return m_inodeContextMenu->addAction(icon, text);
}

QAction *DirectoryListViewWidget::addNoSelectedInodeContextMenuAction(const QString &text)
{
    return m_noSelectedInodeContextMenu->addAction(text);
}

QAction *DirectoryListViewWidget::addNoSelectedInodeContextMenuAction(const QIcon &icon, const QString &text)
{
    return m_noSelectedInodeContextMenu->addAction(icon, text);
}

void DirectoryListViewWidget::onItemDoubleClicked(QListWidgetItem *item)
{
    if (!item)
        return;

    QString pathFromInodeItem = readPathFromNodeItem(item);

    if (!pathFromInodeItem.isEmpty())
        readPath(pathFromInodeItem);
}

void DirectoryListViewWidget::onUpButtonClicked()
{
    QFileInfo currentInodeInfo(m_currentPath);
    setPath(currentInodeInfo.canonicalPath());
}

void DirectoryListViewWidget::onListWidgetContextMenuRequested(QPoint point)
{
    QListWidgetItem *selectedItem = ui->m_directoyrListWidget->itemAt(point);

    if (selectedItem)
        showInodeContextMenu(point);
    else
        showNonSelectionContextMenu(point);
}

void DirectoryListViewWidget::deselectInodes()
{
    QList<QListWidgetItem *> selectedItems = ui->m_directoyrListWidget->selectedItems();

    foreach (QListWidgetItem *item, selectedItems) {
        if (item)
            item->setSelected(false);
    }
}

void DirectoryListViewWidget::listRoot()
{
    ui->m_directoyrListWidget->clear();

    QFileInfoList driveInfoList = QDir::drives();
    updateListView(driveInfoList);
    m_currentPath.clear();
    emit currentDirPathChanged(m_currentPath);
}

void DirectoryListViewWidget::readPath(const QString &path)
{
    if (m_currentPath == path || !QFileInfo(path).isDir())
        return;

    ui->m_directoyrListWidget->clear();

    QDir dir(path);
    QFileInfoList inodeInfoList = dir.entryInfoList(QDir::NoFilter, QDir::DirsFirst);

    updateListView(inodeInfoList);
    m_currentPath = path;
    emit currentDirPathChanged(m_currentPath);
}

void DirectoryListViewWidget::updateListView(const QFileInfoList &inodeInfoList)
{
    foreach (const QFileInfo &inodeInfo, inodeInfoList) {
        QListWidgetItem *inodeItem = createItemForInode(inodeInfo);

        if (inodeItem)
            ui->m_directoyrListWidget->addItem(inodeItem);
    }
}

QListWidgetItem *DirectoryListViewWidget::createItemForInode(const QFileInfo &inodeInfo) const
{
    if (!inodeInfo.exists())
        return 0;

    QString iconPath;

    if (inodeInfo.isRoot())
        iconPath = QLatin1String(":/icons/inode_disk");
    else if (inodeInfo.isDir())
        iconPath = QLatin1String(":/icons/inode_directory");
    else if (inodeInfo.isFile())
        iconPath = QLatin1String(":/icons/inode_file");

    if (!iconPath.isEmpty()) {

        QListWidgetItem *inodeItem = 0;

        if (inodeInfo.isRoot())
            inodeItem = new QListWidgetItem(QIcon(iconPath), inodeInfo.canonicalFilePath());
        else
            inodeItem = new QListWidgetItem(QIcon(iconPath), inodeInfo.fileName());

        setPathInNodeItem(inodeItem, inodeInfo.canonicalFilePath());
        return inodeItem;
    }

    return 0;
}

void DirectoryListViewWidget::setPathInNodeItem(QListWidgetItem *item, const QString &path) const
{
    if (!item || path.isEmpty())
        return;

    item->setData(Qt::UserRole, QVariant(path));
}

QString DirectoryListViewWidget::readPathFromNodeItem(const QListWidgetItem *item) const
{
    if (!item)
        return QString();

    return item->data(Qt::UserRole).toString();
}

void DirectoryListViewWidget::showInodeContextMenu(QPoint point)
{
    if(m_noSelectedInodeContextMenu)
        m_noSelectedInodeContextMenu->hide();

    if (m_inodeContextMenu)
        m_inodeContextMenu->exec(mapToGlobal(point));
}

void DirectoryListViewWidget::showNonSelectionContextMenu(QPoint point)
{
    if (m_inodeContextMenu)
        m_inodeContextMenu->hide();

    if (m_noSelectedInodeContextMenu)
        m_noSelectedInodeContextMenu->exec(mapToGlobal(point));
}

} // namespace DirectoryListView
