#include "mapview.hpp"
#include "ui_mapview.h"
#include "src/datastore/database.hpp"
#include <QSpinBox>

/* Constructor */
MapView::MapView(QWidget *parent) :
View(parent),
m_ui(new Ui::MapView)
{
    m_ui->setupUi(this);
    m_map = new MapPainter(m_ui->map_widget);
    m_ui->spinBox->setRange(50,80);
    m_ui->spinBox_2->setRange(50,80);
}

/* Destructor */
MapView::~MapView()
{
    delete m_ui;
}

/* The resetView function resets the Ui that corresponds with the given view */
void MapView::resetView()
{
    m_map->repaint();
}

/* The resetUi function resets the Ui that corresponds with the given view */
void MapView::resetUi()
{

}

// Only using it to debug/ demo
void MapView::on_pushButton_clicked()
{
    m_map->animateTrip(m_ui->spinBox->value(),m_ui->spinBox_2->value());
}

// Only using it to debug/ demo
void MapView::on_pushButton_2_clicked()
{
    Database::loadFromFile("MLBInformationExpansion.csv");
    Database::loadDistancesFromFile("DistanceBetweenExpansionStadium.csv");
    resetView();
}

