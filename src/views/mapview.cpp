#include "mapview.hpp"
#include "ui_mapview.h"
#include <QPropertyAnimation>
#include <QSpinBox>
#include <cmath>

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

/*
 * Takes From and To coordinates and depending on the direction it set's
 * the plane used for animation to either face right or left
 *
 * @param x1 From: x-coord
 * @param x2 To: x-coord
*/
void MapView::setPlane(int x1, int x2)
{
//    bool isPositive = x1 - x2 < 0;
//    if(isPositive)
        m_ui->plane_widget->setPixmap(QPixmap(":/res/airplane_right.png"));
//    else
//        m_ui->plane_widget->setPixmap(QPixmap(":/res/airplane_left.png"));
    // Raise plane pixmap to be above drawing
    m_ui->plane_widget->raise();
}

/*
 * Takes From and To stadium id's animates a plane starting at
 * froms coordinates and ending at to coordinates
 *
 * @param stadiumOneId From: id
 * @param stadiumTwoId To: id
*/
void MapView::animateTrip(int stadiumOneId, int stadiumTwoId)
{
    std::map<int,Database::coords> tempCoords(Database::getCoordinates());
    setPlane(tempCoords[stadiumOneId].first,tempCoords[stadiumTwoId].first);
    double tempDub = directionAngle(tempCoords[stadiumOneId].first,tempCoords[stadiumOneId].first,tempCoords[stadiumTwoId].first,tempCoords[stadiumTwoId].second);

    QPropertyAnimation* animation = new QPropertyAnimation(m_ui->plane, "geometry");
    animation->setDuration(600);
    animation->setStartValue(QRect(QPoint(tempCoords[stadiumOneId].first,tempCoords[stadiumOneId].second-25),size()));
    animation->setEndValue(QRect(QPoint(tempCoords[stadiumTwoId].first,tempCoords[stadiumTwoId].second-25),size()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// Only using it to debug/ demo
void MapView::on_pushButton_clicked()
{
    animateTrip(m_ui->spinBox->value(),m_ui->spinBox_2->value());
}

// Only using it to debug/ demo
void MapView::on_pushButton_2_clicked()
{
    Database::loadFromFile("./../../../src/datastore/MLBInformationExpansion.csv");
    Database::loadDistancesFromFile("./../../../src/datastore/DistanceBetweenExpansionStadium.csv");
    resetView();
}

/**
 * Given the starting and ending coordinates, calculate the direction
 * angle of the vector pointing from start to finish
 *
 * @param startingX the starting x coordinate
 * @param startingY the starting y coordinate
 * @param endingX the ending x coordinate
 * @param endingY the ending y coordinate
 * @return a direction angle of the vector pointing from start to finish
 */
double MapView::directionAngle(int startingX, int startingY, int endingX, int endingY)
{
    int xComponent = endingX - startingX;
    int yComponent = endingY - startingY;
    double PI = 3.141592653589793238462643383279503;
    double angle = atan((1.0*yComponent)/xComponent) * (180.0 / PI);
    if(xComponent < 0) { angle += 180.0; };

    return angle;
}
