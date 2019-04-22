#include "mapview.hpp"
#include "ui_mapview.h"
#include <QPropertyAnimation>
#include <QSpinBox>

MapView::MapView(QWidget *parent) :
View(parent),
m_ui(new Ui::MapView)
{
    m_ui->setupUi(this);
    m_map = new MapPainter(m_ui->map_widget);
    m_ui->spinBox->setRange(50,80);
    m_ui->spinBox_2->setRange(50,80);
}

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

void MapView::on_pushButton_clicked()
{
    animateTrip(m_ui->spinBox->value(),m_ui->spinBox_2->value());
}

/*
 * Takes From and To coordinates and depending on the direction it set's
 * the plane used for animation to either face right or left
 *
 * @param x1 From: x-coord
 * @param x2 To: x-coord
*/
void MapView::setPlane(int x1, int x2)
{
    bool isPositive = x1 - x2 < 0;
    if(isPositive)
        m_ui->plane_widget->setPixmap(QPixmap(":/res/airplane_right.png"));
    else
        m_ui->plane_widget->setPixmap(QPixmap(":/res/airplane_left.png"));
}

void MapView::animateTrip(int stadiumOneId, int stadiumTwoId)
{
    std::map<int,Database::coords> tempCoords(Database::getCoordinates());
    setPlane(tempCoords[stadiumOneId].first,tempCoords[stadiumTwoId].first);
    QPropertyAnimation* animation = new QPropertyAnimation(m_ui->plane, "geometry");
    animation->setDuration(600);
    animation->setStartValue(QRect(QPoint(tempCoords[stadiumOneId].first,tempCoords[stadiumOneId].second-25),size()));
    animation->setEndValue(QRect(QPoint(tempCoords[stadiumTwoId].first,tempCoords[stadiumTwoId].second-25),size()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MapView::on_pushButton_2_clicked()
{
    Database::loadFromFile("./../../../src/datastore/MLBInformationExpansion.csv");
    Database::loadDistancesFromFile("./../../../src/datastore/DistanceBetweenExpansionStadium.csv");
    resetView();
}
