#ifndef DIRECTORYVIEWWIDGET_H
#define DIRECTORYVIEWWIDGET_H

#include <QFrame>

#include "common.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

namespace DirectoryViewPlugin
{

class DirectoryViewWidget : public QFrame
{
    Q_OBJECT

public:
    explicit DirectoryViewWidget(QWidget *parent = 0);
    ~DirectoryViewWidget();

    void setIconSize(IconSize size);

private:
};

} // namespace DirectoryViewPlugin

#endif // DIRECTORYVIEWWIDGET_H
