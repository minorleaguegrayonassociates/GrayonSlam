#include "beacon.hpp"
#include <QPainter>
#include <QTimer>

// Value used to set Beacon outside of the map widget's view, Default point
const QPoint outerBound(-10,-10);

/* Constructor */
Beacon::Beacon(QWidget* parent)
    : QWidget(parent), m_coords(outerBound)
{
    // Resize widget to parents width and height
    this->resize(parent->size());
}

/*
 * Draw's Beacon at the coordinates provided
 *
 * @param painter QPainter
 * @param stadiumTwo To: QPoint(x,y)
*/
void Beacon::drawBeacon(QPainter& painter, const QPoint& stadiumCoord)
{
    QPen myPen;

    /* set myPen info */
    myPen.setWidth(1);
    myPen.setColor(Qt::GlobalColor::green);
    myPen.setCapStyle(Qt::PenCapStyle::MPenCapStyle);
    myPen.setJoinStyle(Qt::PenJoinStyle::MiterJoin);
    myPen.setStyle(Qt::PenStyle::SolidLine);

    // set painters pen to myPen
    painter.setPen(myPen);

    /* Draw's 4 different size circles */
    for(int i  = 1; i < 5; ++i)
        painter.drawEllipse(stadiumCoord,4*i,4*i);
}

/*
 * Takes To: stadium coordinate a QPoint(x,y)
 *  and animates a beacon eminating from the coordinates provided
 *
 * @param stadiumTwo To: QPoint(x,y)
*/
void Beacon::setCoords(const QPoint& stadiumCoord)
{
    m_coords = stadiumCoord;
    repaint();
}

/**
 * Draws a beacon signal at the given coordinates
 */
void Beacon::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Draw beacon at m_coords
    drawBeacon(painter,m_coords);
}

/**
 * Event triggers when item is hidden and singleShot is called to set Beacon to show
 */
void Beacon::hideEvent(QHideEvent*)
{
    QTimer::singleShot(300, this, [this](){return this->setHidden(false);});
}

/**
 * Event triggers when item is showing and singleShot is called to set Beacon to hidden
 */
void Beacon::showEvent(QShowEvent*)
{
    QTimer::singleShot(300, this->parent(), [this](){return this->setHidden(true);});
}
