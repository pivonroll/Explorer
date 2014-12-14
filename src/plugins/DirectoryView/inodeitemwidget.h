#ifndef DIRECTORYITEMWIDGET_H
#define DIRECTORYITEMWIDGET_H

#include <QFrame>

#include "directoryview_global.h"
#include "common.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace DirectoryViewPlugin
{

class DIRECTORYVIEWSHARED_EXPORT InodeItemWidget : public QFrame
{
    Q_OBJECT

    static const int BORDER_WIDTH = 1;
public:
    enum VisualState {
        Normal,
        Hover,
        Focus,
        FocusAndHover,
        Selected
    };

    enum InodeType {
        Directory,
        File
    };

    explicit InodeItemWidget(QWidget *parent = 0);
    ~InodeItemWidget();

    QString displayText() const;
    void setDisplayText(const QString &displayText);

    InodeType inodeType() const;
    void setInodeType(const InodeType &inodeType);

    VisualState currentVisualState() const;
    void setCurrentVisualState(const VisualState &currentVisualState);

    IconSize iconSize() const;
    void setIconSize(const IconSize &iconSize);

    Qt::Orientation contentOrientation() const;
    void setContentOrientation(const Qt::Orientation &contentOrientation);

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *keyEvent);

signals:
    void enterInodeRequested();
    void focusPreviousRequested();
    void focusNextRequested();
    void selected();
    void unselected();

private:
    void createAndSetStyleSheet();
    QString generateIconImageStyleSheet();
    void adjustSize();
    void setVerticalLayout();
    void setHorizontalLayout();

    QString m_displayText;
    InodeType m_inodeType;

    VisualState m_currentVisualState;
    VisualState m_previousVisualState;

    QPoint m_mousePressedPosition;
    IconSize m_iconSize;

    QFrame *m_iconFrame;
    QFrame *m_freeSpaceFrame;
    QLabel *m_textLabel;

    Qt::Orientation m_contentOrientation;
};

} // namespace DirectoryViewPlugin

#endif // DIRECTORYITEMWIDGET_H
