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

/* The resetView function resets the Ui that corresponds with the given view */
void MapView::resetView()
{
    m_mapPainter->repaint();
    resetUi();
}

/* The resetUi function resets the Ui that corresponds with the given view */
void MapView::resetUi()
{
    m_mapPainter->resetUi();
}
