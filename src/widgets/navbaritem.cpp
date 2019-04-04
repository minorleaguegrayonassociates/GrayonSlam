#include "navbaritem.hpp"
#include "ui_navbaritem.h"
#include <QFont>

/* Constructor */
NavBarItem::NavBarItem(QListWidget* parent, QString icon, QString label)
    : QWidget(parent), m_ui(new Ui::NavBarItem)
{
    m_ui->setupUi(this);

    /* fontAwesome has built-in icons */
    QFont font;
    font.setFamily("Font Awesome 5 Free");

    /* Label */
    m_ui->navLabel->setWordWrap(true);
    font.setPixelSize(16);
    m_ui->navLabel->setFont(font);
    m_ui->navLabel->setText(label);
    m_ui->navLabel->hide(); //starts off hidden

    /* Icon */
    font.setPixelSize(38);
    m_ui->navIcon->setFont(font);
    m_ui->navIcon->setText(icon);

    setStyleSheet("* { color: white; }");
}

/* Destructor */
NavBarItem::~NavBarItem()
{
    delete m_ui;
}

/* Public slots */
void NavBarItem::expand() const
{
    m_ui->navLabel->show();
}

void NavBarItem::shrink() const
{
    m_ui->navLabel->hide();
}

/* Events */
void NavBarItem::enterEvent(QEvent*)
{
    setStyleSheet("QWidget#navIcon,QWidget#navLabel { color: black; }");
}

void NavBarItem::leaveEvent(QEvent*)
{
    setStyleSheet("QWidget#navIcon,QWidget#navLabel { color: white; }");
}
