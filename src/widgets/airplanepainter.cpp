#include "airplanepainter.hpp"
#include "ui_airplanepainter.h"
#include <QPainter>
#include <cmath>

/* size of plane */
const QSize planeSize(25,25);
/* Used to center painter while rotating painter mid-point of plane widget */
const QPoint translateCenter(planeSize.width()/2,planeSize.height()/2);
/* set's value back to original point if translateCenter was used to translate painter for painting plane widget */
const QPoint translateReset(planeSize.width()/2-planeSize.width(),planeSize.height()/2-planeSize.height());

AirplanePainter::AirplanePainter(QWidget *parent)
    : QWidget(parent), m_plane(":/res/airplane.png")
{}

/**
 * Draws all stadiums and all the edges between the stadiums
 */
void AirplanePainter::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.translate(translateCenter);
    painter.rotate(rotate);
    painter.translate(translateReset);
    painter.drawPixmap(QRect(QPoint(0,0),planeSize), m_plane);
    painter.end();
}

/**
 * Given the starting and ending coordinates, calculate the direction
 * angle of the vector pointing from start to finish, set `rotate` and repaint
 *
 * @param startingX the starting x coordinate
 * @param startingY the starting y coordinate
 * @param endingX the ending x coordinate
 * @param endingY the ending y coordinate
 */
void AirplanePainter::setRotation(int startingX, int startingY, int endingX, int endingY)
{
    int xComponent = endingX - startingX;
    int yComponent = endingY - startingY;
    double PI = 3.141592653589793238462643383279503;
    double angle = atan((1.0*yComponent)/xComponent) * (180.0 / PI);
    if(xComponent < 0) { angle += 180.0; };
    rotate = angle;
    repaint();
}
