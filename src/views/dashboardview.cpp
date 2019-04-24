#include "dashboardview.hpp"
#include "ui_dashboardview.h"

DashboardView::DashboardView(QWidget *parent)
    : View(parent), m_ui(new Ui::DashboardView)
{
    m_ui->setupUi(this);

    /* Initialize slideshow with images an  d play it */
    m_slideshow = new ImageSlideshow(m_ui->widget, 2000);
    m_slideshow->addImage(QPixmap(":/res/background_icons_blue.png"));
    m_slideshow->addImage(QPixmap(":/res/background_icons_orange.png"));
    m_slideshow->play();
}

DashboardView::~DashboardView()
{
    delete m_ui;
}
