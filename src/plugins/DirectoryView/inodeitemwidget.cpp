#include "inodeitemwidget.h"

#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include <QDebug>

namespace DirectoryViewPlugin
{

const char ICON_FRAME[] = "IconFrame";

InodeItemWidget::InodeItemWidget(QWidget *parent)
    : QFrame(parent),
      m_currentVisualState(Normal),
      m_previousVisualState(Normal),
      m_inodeType(Directory)
{
    setObjectName("InodeItemWidget");
    setFocusPolicy(Qt::StrongFocus);
    createAndSetStyleSheet();

    m_freeSpaceFrame = new QFrame;

    QString style;
    style.append(QLatin1String("QFrame\n{\n") +
                 " background-color: transparent;" +
                 "\n}\n");
    m_freeSpaceFrame->setStyleSheet(style);

    m_iconFrame = new QFrame(this);
    m_iconFrame->setObjectName(objectName() + QLatin1String(ICON_FRAME));
    m_textLabel = new QLabel(this);
    m_textLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // set icon size and ajdust widget's size and layout according to icon size
    m_iconSize = IconSize_16;

    m_iconSize != IconSize_16 ? setVerticalLayout() : setHorizontalLayout();

    createAndSetStyleSheet();
    adjustSize();
}

InodeItemWidget::~InodeItemWidget()
{
}

QString InodeItemWidget::displayText() const
{
    return m_textLabel->text();
}

void InodeItemWidget::setDisplayText(const QString &displayText)
{
    m_textLabel->setText(displayText);
}

IconSize InodeItemWidget::iconSize() const
{
    return m_iconSize;
}

void InodeItemWidget::setIconSize(const IconSize &iconSize)
{
    if (iconSize == m_iconSize)
        return;

    if (iconSize != IconSize_16 && m_iconSize == IconSize_16)
        setVerticalLayout();

    else if (iconSize == IconSize_16 && m_iconSize != IconSize_16)
        setHorizontalLayout();

    m_iconSize = iconSize;
    createAndSetStyleSheet();
    adjustSize();
}

InodeItemWidget::VisualState InodeItemWidget::currentVisualState() const
{
    return m_currentVisualState;
}

void InodeItemWidget::setCurrentVisualState(const VisualState &currentVisualState)
{
    m_currentVisualState = currentVisualState;
    createAndSetStyleSheet();
}

InodeItemWidget::InodeType InodeItemWidget::inodeType() const
{
    return m_inodeType;
}

void InodeItemWidget::setInodeType(const InodeType &inodeType)
{
    m_inodeType = inodeType;
    createAndSetStyleSheet();
}

void InodeItemWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

    if (m_currentVisualState == Selected)
        return;

    else if (m_currentVisualState == Focus) {
        m_currentVisualState = FocusAndHover;
        m_previousVisualState = Focus;
    }
    else {
        m_previousVisualState = m_currentVisualState;
        m_currentVisualState = Hover;
    }

    createAndSetStyleSheet();
}

void InodeItemWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)

    if (m_currentVisualState == Selected)
        return;

    m_currentVisualState = m_previousVisualState;
    createAndSetStyleSheet();
}

void InodeItemWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_mousePressedPosition = mouseEvent->pos();

    if (m_currentVisualState != Selected) {
        m_currentVisualState = Selected;
        createAndSetStyleSheet();
        emit selected();
    }
    else {
        if (mouseEvent->modifiers() & Qt::ControlModifier) {
            m_currentVisualState = FocusAndHover;
            createAndSetStyleSheet();
        }
    }
}

void InodeItemWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)
}

void InodeItemWidget::mouseReleaseEvent(QMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)
}

void InodeItemWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    Q_UNUSED(keyEvent)
}

void InodeItemWidget::createAndSetStyleSheet()
{
    int padding = 35;

    if (m_displayText.contains("\n"))
        padding = 45;

    QString style;
    switch (m_currentVisualState) {
    case InodeItemWidget::Normal:
    {
        style.append("QFrame#" + objectName() +
                     " {\n" +
                     " background-color: transparent;" +
                     " border-width: " + QVariant(BORDER_WIDTH).toString() + "px;" +
                     " border-style: solid;" +
                     " border-color: transparent; " +
                     "\n}" +
                     "\n");
    }
        break;
    case InodeItemWidget::Hover:
    {
        style.append("QFrame#" + objectName() +
                     " {\n " +
                     " background-color: #ebf3fd;" +
                     " border-width: " + QVariant(BORDER_WIDTH).toString() + "px;" +
                     " border-style: solid;" +
                     " border-color: #b8d6fb;" +
                     " \n}" +
                     "\n");
    }
        break;
    case InodeItemWidget::Focus:
    {
        style.append("QFrame#" + objectName() +
                     " {\n " +
                     " background-color: transparent;" +
                     " border-width: " + QVariant(BORDER_WIDTH).toString() + "px;" +
                     " border-style: solid;" +
                     " border-color: #7da2ce;" +
                     " \n}" +
                     "\n");
    }
        break;
    case InodeItemWidget::FocusAndHover:
    {
        style.append("QFrame#" + objectName() +
                     " {\n " +
                     " background-color: #ebf3fd;" +
                     " border-width: " + QVariant(BORDER_WIDTH).toString() + "px;" +
                     " border-style: solid;" +
                     " border-color: #7da2ce;" +
                     " \n}" +
                     "\n");
    }
        break;
    case InodeItemWidget::Selected:
    {
        style.append("QFrame#" + objectName() +
                     " {\n " +
                     " background-color: #c1dcfc;" +
                     " border-width: " + QVariant(BORDER_WIDTH).toString() + "px;" +
                     " border-color: #7da2ce;" +
                     " border-style: solid;" +
                     " \n}" +
                     "\n");
    }
        break;
    default:
        return;
    }

    style += generateIconImageStyleSheet();

    setStyleSheet(style);
}

QString InodeItemWidget::generateIconImageStyleSheet()
{
    QString imageUrl;

    switch (m_inodeType) {
    case InodeItemWidget::Directory:
        imageUrl = ":/icons/inode_directory_";
        break;
    case InodeItemWidget::File:
        imageUrl = ":/icons/inode_file_";
        break;
    default:
        return QString();
    }

    switch (m_iconSize) {
    case IconSize_16:
        imageUrl += "16";
        break;
    case IconSize_32:
        imageUrl += "32";
        break;
    case IconSize_48:
        imageUrl += "48";
        break;
    case IconSize_64:
        imageUrl += "64";
        break;
    case IconSize_128:
        imageUrl += "128";
        break;
    default:
        return QString();
    }

    QString style;
    style.append("QFrame#" + objectName() + QString(ICON_FRAME) +
                 " {\n " +
                 " border-image: url(" + imageUrl + ");" +
                 " background-color: transparent;" +
                 " \n}" +
                 "\n");
    return style;
}

void InodeItemWidget::adjustSize()
{
    int iconFrameSize = 0;
    int topSpace = 0;
    int bottomSpace = 0;
    int leftSpace = 0;
    int rightSpace = 0;
    int spacing = 0;

    if (layout())
        spacing = layout()->spacing();

    switch (m_iconSize) {
    case IconSize_16:
        iconFrameSize = 16;
        topSpace = 2;
        bottomSpace = 2;
        leftSpace = 2;
        break;
    case IconSize_32:
        iconFrameSize = 32;
        topSpace = 4;
        leftSpace = rightSpace = 8;
        bottomSpace = 5;
        break;
    case IconSize_48:
        iconFrameSize = 48;
        topSpace = 5;
        leftSpace = rightSpace = 16;
        bottomSpace = 5;
        break;
    case IconSize_64:
        iconFrameSize = 64;
        topSpace = 5;
        leftSpace = rightSpace = 20;
        bottomSpace = 5;
        break;
    case IconSize_128:
        iconFrameSize = 128;
        topSpace = 6;
        leftSpace = rightSpace = 22;
        bottomSpace = 6;
        break;
    }

    m_iconFrame->setFixedSize(iconFrameSize, iconFrameSize);

    if (m_iconSize != IconSize_16) {

        int contentWidth = 0;
        if (m_iconFrame->width() > m_textLabel->width())
            contentWidth = m_iconFrame->width();
        else {
            contentWidth = m_textLabel->width();
            leftSpace = rightSpace = 0;
        }

        QMargins margins(leftSpace, topSpace, rightSpace, bottomSpace);
        layout()->setContentsMargins(margins);

        setFixedHeight(BORDER_WIDTH +
                       margins.top() +
                       m_iconFrame->height() +
                       m_textLabel->fontMetrics().height() +
                       margins.bottom() +
                       BORDER_WIDTH);

        setFixedWidth(BORDER_WIDTH +
                      margins.left() +
                      contentWidth +
                      margins.right() +
                      BORDER_WIDTH);
    } else {
        QMargins margins(leftSpace, topSpace, rightSpace, bottomSpace);
        layout()->setContentsMargins(margins);

        setFixedHeight(BORDER_WIDTH +
                       margins.top() +
                       m_iconFrame->height() +
                       margins.bottom() +
                       BORDER_WIDTH);
        setFixedWidth(230);
    }
}

void InodeItemWidget::setVerticalLayout()
{
    QLayout *oldLayout = layout();

    if (oldLayout)
        oldLayout->deleteLater();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setDirection(QBoxLayout::BottomToTop);
    mainLayout->addWidget(m_textLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_iconFrame, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_freeSpaceFrame, 1);
    setLayout(mainLayout);
    mainLayout->setSpacing(3);
}

void InodeItemWidget::setHorizontalLayout()
{
    QLayout *oldLayout = layout();

    if (oldLayout)
        oldLayout->deleteLater();

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_iconFrame, 0, Qt::AlignVCenter);
    mainLayout->addWidget(m_textLabel, 0, Qt::AlignVCenter);
    mainLayout->addWidget(m_freeSpaceFrame, 1);
    setLayout(mainLayout);
    mainLayout->setSpacing(3);
}

Qt::Orientation InodeItemWidget::contentOrientation() const
{
    return m_contentOrientation;
}

void InodeItemWidget::setContentOrientation(const Qt::Orientation &contentOrientation)
{
    if (m_contentOrientation == contentOrientation)
        return;

    m_contentOrientation = contentOrientation;

    if (m_contentOrientation == Qt::Horizontal)
        setHorizontalLayout();
    else
        setVerticalLayout();
}

} // namespace DirectoryViewPlugin
