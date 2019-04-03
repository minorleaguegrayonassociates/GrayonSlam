#include "navbar.hpp"
#include "navitem.hpp"
#include <QPropertyAnimation>

/**
 * @brief Constructor
 *
 * Constructs a NavBar object. It will resize its parent widget to
 * whatever initial size it needs to be and its current height.
 *
 * @param parent The parent widget the bar will be contained in
 * @param minWidth Minimum width the bar will shrink to
 * @param maxWidth Maximum width the bar will expand to
 */
NavBar::NavBar(QWidget* parent, int minWidth, int maxWidth)
    : QListWidget(parent), m_minWidth(minWidth), m_maxWidth(maxWidth)
{
    parent->raise();
    setStyleSheet("QListWidget { background-color: #303030; }"
                  "QListWidget::item:hover { background-color: white; }");

    //Initial size
    resize(m_minWidth, parent->height());

    //Sets the parent's size
    parent->resize(m_minWidth, parent->height());

    /* Setting background color for highlight - when NavItem is selected this will be it's background color */
    QPalette palette;
    palette.setColor(QPalette::Disabled, QPalette::Highlight, Qt::darkBlue);
    palette.setColor(QPalette::Inactive, QPalette::Highlight, Qt::darkBlue);
    palette.setColor(QPalette::Active, QPalette::Highlight,  Qt::darkBlue);
    this->setPalette(palette);

}

/**
 * @brief Set height of the bar
 *
 * Sets the height of the bar and its parent.
 * Not changing its parent will end up cutting off the bar.
 *
 * @param height The new height of the bar and its parent
 */
void NavBar::setHeight(int height)
{
    resize(width(), height);
    parentWidget()->resize(width(), height);
}

/**
 * @brief Set minimum width of the bar
 *
 * Sets the minimum width of the bar.
 *
 * @param width The new minimum width
 */
void NavBar::setMinWidth(int width)
{
    m_minWidth = width;
}

/**
 * @brief Set maximum width of the bar
 *
 * Sets the maximum width of the bar.
 *
 * @param width The new maximum width
 */
void NavBar::setMaxWidth(int width)
{
    m_maxWidth = width;
}

/**
 * @brief Add button to the bar
 *
 * Adds a new button to the bar using the given strings.
 * Since NavBar uses "Font Awesome 5 Free", all unicode
 * string icons should be represented by that font.
 *
 * @param icon The unicode representation (ex. \uffff) of the icon using the"Font Awesome 5 Free" font
 * @param label The label of the button
 */
void NavBar::addItem(QString icon, QString label)
{
    const QSize itemSize(70, 80);

    QListWidgetItem* listWidgetItem = new QListWidgetItem(this);
    listWidgetItem->setSizeHint(itemSize);
    QListWidget::addItem(listWidgetItem);

    /* Set the QListWidgetItem to hold a NavItem */
    NavItem* navItem = new NavItem(this, icon, label);
    setItemWidget(listWidgetItem, navItem);

    /* Allows the NavBar and NavItem to expand and shrink simultaneously */
    connect(this, &NavBar::expand, navItem, &NavItem::expand);
    connect(this, &NavBar::shrink, navItem, &NavItem::shrink);
}

/**
 * @brief Shrinks the bar
 *
 * Overrides QWidget::leaveEvent(QEvent*).
 * When the cursor leaves the widget, the bar shrinks.
 * The parent widget is also resizes to prevent cutting off.
 * The NavBar::shrink() signal is emitted to tell its buttons to hide its labels.
 */
void NavBar::leaveEvent(QEvent*)
{
    /* Shrinking animation for parent widget */
    QPropertyAnimation* animation = new QPropertyAnimation(parentWidget(), "size");
    animation->setDuration(75);
    animation->setStartValue(size());
    animation->setEndValue(QSize(m_minWidth, height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    /* Shrinking animation for list widget */
    animation = new QPropertyAnimation(this, "size");
    animation->setDuration(75);
    animation->setStartValue(size());
    animation->setEndValue(QSize(m_minWidth, height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    //Tells each NavItem to shrink
    emit shrink();
}

/**
 * @brief Expands the bar
 *
 * Overrides QWidget::enterEvent(QEvent*).
 * When the cursor enters the widget, the bar expands.
 * The parent widget is also resizes to prevent overlaying issues.
 * The NavBar::expand() signal is emitted to tell its buttons to show its labels.
 */
void NavBar::enterEvent(QEvent*)
{
    /* Expanding animation for parent widget */
    QPropertyAnimation* animation = new QPropertyAnimation(parentWidget(), "size");
    animation->setDuration(75);
    animation->setStartValue(size());
    animation->setEndValue(QSize(m_maxWidth, height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    /* Expanding animation for list widget */
    animation = new QPropertyAnimation(this, "size");
    animation->setDuration(75);
    animation->setStartValue(size());
    animation->setEndValue(QSize(m_maxWidth, height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    //Tells each NavItem to expand
    emit expand();
}
