#include "mapview.hpp"
#include "ui_mapview.h"
#include "src/datastore/database.hpp"
#include <QSpinBox>

/* Constructor */
MapView::MapView(QWidget *parent)
    : View(parent), m_ui(new Ui::MapView)
{
    m_ui->setupUi(this);
    m_mapPainter = new MapPainter(m_ui->map_widget);
    m_ui->spinBox->setRange(50,80);
    m_ui->spinBox_2->setRange(50,80);

    testVector = new std::vector<Database::completedEdge>;

    testVector->push_back(std::tuple<int,int,int>(50,58,100));
    testVector->push_back(std::tuple<int,int,int>(58,61,100));
    testVector->push_back(std::tuple<int,int,int>(61,65,100));
    testVector->push_back(std::tuple<int,int,int>(65,66,100));
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

// Only using it to debug/ demo
void MapView::on_pushButton_clicked()
{
    m_mapPainter->animateTrip(m_ui->spinBox->value(),m_ui->spinBox_2->value());
}

// Only using it to debug/ demo
void MapView::on_pushButton_2_clicked()
{
    m_mapPainter->setDiscoveredVector(*testVector);
    m_mapPainter->repaint();
}

