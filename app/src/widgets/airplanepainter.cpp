#include "airplanepainter.hpp"
#include <QPainter>
#include <cmath>

// paint origin
const QPoint origin(0,0);
// Public static const that holds a QSize of the planes size
const QSize AirplanePainter::planeSize(26,26);
// Used to center painter while rotating painter mid-point of plane widget
const QPoint translateCenter(AirplanePainter::planeSize.width()/2,AirplanePainter::planeSize.height()/2);
// set's value back to original point if translateCenter was used to translate painter for painting plane widget
const QPoint translateReset(AirplanePainter::planeSize.width()/2-AirplanePainter::planeSize.width(),
                            AirplanePainter::planeSize.height()/2-AirplanePainter::planeSize.height());

/* Constructor */
AirplanePainter::AirplanePainter(QWidget* parent)
    : QWidget(parent), m_plane(":/res/airplane.png")
{}

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
    double angle = atan2((1.0*yComponent),(1.0*xComponent)) * (180.0/ M_PI);
    angleValue = angle;
    repaint();
}

/**
 * Draws plane at the angle within angleValue
 */
void AirplanePainter::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    /* Rotate plane at the center of the widget */
    painter.translate(translateCenter);
    painter.rotate(angleValue);
    painter.translate(translateReset);

    // Paint m_plane at `origin` (x:0,y:0), size `planeSize` (26 x 26)
    painter.drawPixmap(QRect(origin,planeSize), m_plane);
}
