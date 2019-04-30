#include "mapview.hpp"
#include "ui_mapview.h"
#include "src/datastore/database.hpp"

/* Constructor */
MapView::MapView(QWidget *parent)
    : View(parent), m_ui(new Ui::MapView)
{
    m_ui->setupUi(this);
    m_mapPainter = new MapPainter(m_ui->map_widget);
}

/* Destructor */
MapView::~MapView()
{
    delete m_ui;
    delete m_mapPainter;
}

/* Resets */
void MapView::resetView()
{
    m_mapPainter->repaint();
    MapView::resetUi();
}

void MapView::resetUi()
{
    m_mapPainter->resetMap();
}

void MapView::setAnimation(const int& stadiumFrom,const int& stadiumTo)
{
    m_mapPainter->animateTrip(stadiumFrom,stadiumTo);
}

void MapView::on_goToShop_clicked()
{
    emit goToShop();
}
