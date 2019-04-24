#include "airplanepainter.hpp"
#include <QPainter>
#include <cmath>

/* paint origin */
const QPoint origin(0,0);
/* size of plane */
const QSize planeSize(26,26);
/* Used to center painter while rotating painter mid-point of plane widget */
const QPoint translateCenter(planeSize.width()/2,planeSize.height()/2);
/* set's value back to original point if translateCenter was used to translate painter for painting plane widget */
const QPoint translateReset(planeSize.width()/2-planeSize.width(),planeSize.height()/2-planeSize.height());

/* Constructor */
AirplanePainter::AirplanePainter(QWidget *parent)
   : QWidget(parent), m_plane(":/res/airplane.png")
{}

/**
 * Draws plane at the angle within angleValue
 */
void AirplanePainter::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.translate(translateCenter);
    painter.rotate(angleValue);
    painter.translate(translateReset);
    painter.drawPixmap(QRect(origin,planeSize), m_plane);
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
    angleValue = angle;
    repaint();
}
