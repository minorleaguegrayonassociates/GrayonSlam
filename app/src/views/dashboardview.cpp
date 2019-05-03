#include "dashboardview.hpp"
#include "ui_dashboardview.h"
#include "src/utils/parser.hpp"
#include <QRandomGenerator>

/* Static variables */
std::vector<std::vector<std::string>> DashboardView::splashes;

DashboardView::DashboardView(QWidget* parent)
    : View(parent), m_ui(new Ui::DashboardView)
{
    m_ui->setupUi(this);

    loadSplashes();

    /* Initialize slideshow with images and play it */
    m_slideshow = new ImageSlideshow(m_ui->widget_slideshow, 2000);
    m_slideshow->addImage(QPixmap(":/res/slideshow/BigLeagueChew.png"), Qt::KeepAspectRatio);
    m_slideshow->addImage(QPixmap(":/res/slideshow/engineer.jpg"), Qt::KeepAspectRatio);
    m_slideshow->addImage(QPixmap(":/res/slideshow/angels.jpg"), Qt::KeepAspectRatio);
    m_slideshow->addImage(QPixmap(":/res/slideshow/angelsfront.jpg"), Qt::KeepAspectRatio);
    m_slideshow->addImage(QPixmap(":/res/slideshow/wrigleyfront.jpg"), Qt::KeepAspectRatio);
    m_slideshow->addImage(QPixmap(":/res/slideshow/bitgo.png"), Qt::KeepAspectRatio);
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

/**
 * Calls @a resetUi().
 */
void DashboardView::resetView()
{
    resetUi();
}

/**
 * Resets the splash message and other UI elements.
 */
void DashboardView::resetUi()
{
    /* Reset the splash message */
    int randIndex = QRandomGenerator::global()->generate() % splashes.size();
    std::string splash = splashes[randIndex].front();
    m_ui->label_splash->setText(QString::fromStdString(splash));
}

/**
 * Loads the splashes from a file.
 */
void DashboardView::loadSplashes()
{
    splashes = loadData("splash.csv");
}
