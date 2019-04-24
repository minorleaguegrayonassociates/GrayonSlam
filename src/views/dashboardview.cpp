#include "dashboardview.hpp"
#include "ui_dashboardview.h"

DashboardView::DashboardView(QWidget* parent)
    : View(parent), m_ui(new Ui::DashboardView)
{
    m_ui->setupUi(this);

    /* Initialize slideshow with images and play it */
    m_slideshow = new ImageSlideshow(m_ui->widget, 2000);
    m_slideshow->addImage(QPixmap(":/res/slideshow/BigLeagueChew.png"));
    m_slideshow->addImage(QPixmap(":/res/slideshow/engineer.jpg"));
    m_slideshow->start();
}

/**
 * Deletes all widgets.
 */
DashboardView::~DashboardView()
{
    delete m_ui;
    delete m_slideshow;
}
