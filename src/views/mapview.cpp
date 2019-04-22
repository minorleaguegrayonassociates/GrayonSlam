#include "mapview.hpp"
#include "ui_mapview.h"
#include <QPropertyAnimation>

MapView::MapView(QWidget *parent) :
View(parent),
m_ui(new Ui::MapView)
{
    m_ui->setupUi(this);
    m_map = new MapPainter(m_ui->map_widget);
}

MapView::~MapView()
{
    delete m_ui;
}

/* The resetView function resets the Ui that corresponds with the given view */
void MapView::resetView()
{

}

/* The resetUi function resets the Ui that corresponds with the given view */
void MapView::resetUi()
{

}

void MapView::on_pushButton_clicked()
{
    QPropertyAnimation* animation = new QPropertyAnimation(m_ui->plane, "geometry");
    animation->setDuration(350);
    animation->setStartValue(QRect(QPoint(0,0),QSize(50,50)));
    animation->setEndValue(QRect(QPoint(100,100),QSize(50,50)));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    Database::loadFromFile("./../../../src/datastore/MLBInformationExpansion.csv");
    Database::loadDistancesFromFile("./../../../src/datastore/DistanceBetweenExpansionStadium.csv");
    m_map->repaint();
    setPlane(9,10);
}

void MapView::setPlane(int x1, int x2)
{
    bool isPositive = x1 - x2 > 0;
    if(isPositive)
        m_ui->plane_widget->setPixmap(QPixmap(":/res/airplane_right.png"));
    else
        m_ui->plane_widget->setPixmap(QPixmap(":/res/airplane_left.png"));
}
