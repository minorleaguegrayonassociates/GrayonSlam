#include "mappainter.hpp"
#include "ui_mappainter.h"
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

/* Constuctor */
MapPainter::MapPainter(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::MapPainter)
{
    m_ui->setupUi(this);
}

/* Destuctor */
MapPainter::~MapPainter()
{
    delete m_ui;
}

/**
 * Draws all stadiums and all the edges between the stadiums
 */
void MapPainter::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    std::map<int,Database::coords> tempCoords(Database::getCoordinates());

    /* Paint edge between stadiums */
    for(auto edge : Database::getDistances())
    {
        paintEdge(painter,QPoint(tempCoords.find(std::get<0>(edge))->second.first,tempCoords.find(std::get<0>(edge))->second.second),
                          QPoint(tempCoords.find(std::get<1>(edge))->second.first,tempCoords.find(std::get<1>(edge))->second.second));
    }

    /* Paint stadium (red or blue based on league) and print the name of the stadium */
    for(auto pair : tempCoords)
    {
        paintStadiums(painter, pair.first,QPoint(pair.second.first,pair.second.second),
                      QString::fromStdString(Database::findStadiumById(pair.first).getName()));
    }
    painter.end();
}

/**
 * Draws stadium and it's name at the given coordinate
 *
 * @param painter QPainter
 * @param id stadium id - used to find it's team league and draw the correct color
 * @param stadiumCoordinate QPoint - x, y coordinates where the stadium and text will be drawn
 * @param stadiumName QString name of stadium, will be drawn at the coordinate provided
 */
void MapPainter::paintStadiums(QPainter& painter,int id, const QPoint& stadiumCoordinate, const QString& stadiumName)
{
    QBrush myBrush;
    QPen myPen;
    /* If the leage is National set pen and brush blue, else set them red */
    if(Database::findTeamById(Database::findStadiumById(id).getTeamId()).league == Team::League::NATIONAL)
    {
        myBrush.setColor(Qt::GlobalColor::blue);
        myPen.setColor(Qt::GlobalColor::blue);
    }
    else
    {
        myBrush.setColor(Qt::GlobalColor::red);
        myPen.setColor(Qt::GlobalColor::red);
    }
    /* set myPen info */
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    //set brush style
    myBrush.setStyle(Qt::BrushStyle::SolidPattern);
    /* set painters pen and brush to myPen and myBrush */
    painter.setBrush(myBrush);
    painter.setPen(myPen);
    // Draw stadium
    painter.drawEllipse(stadiumCoordinate, 1, 1);
    // Draw stadium name
    paintText(painter, stadiumCoordinate, stadiumName);
}

/**
 * Draws draws line between the coordinates provided
 *
 * @param painter QPainter
 * @param stadiumCoord1 QPoint - x, y coordinates where the line where start
 * @param stadiumCoord2 QPoint - x, y coordinates where the line will end
 */
void MapPainter::paintEdge(QPainter& painter, const QPoint& stadiumCoord1, const QPoint& stadiumCoord2)
{
    QPen myPen;
    /* set myPen info */
    myPen.setColor(Qt::GlobalColor::black);
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::DotLine);
    // set pen myPen
    painter.setPen(myPen);
    /* adjust line so it sits a bit closer to the center of the stadium circle */
    QPoint one = stadiumCoord1 + QPoint(1,1);
    QPoint two = stadiumCoord2 - QPoint(1,1);
    // Draw Line
    painter.drawLine(one, two);
}

/**
 * Draws text at the coordinates provided
 *
 * @param painter QPainter
 * @param coordinate QPoint - x, y coordinates where text will be printed
 * @param strToPrint QString that will be printed
 */
void MapPainter::paintText(QPainter& painter, const QPoint& coordinate, const QString& strToPrint)
{
    QPen myPen;
    /* set pen info */
    myPen.setWidth(1);
    myPen.setColor(Qt::GlobalColor::black);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    /* set font info */
    QFont myFont=painter.font() ;
    myFont.setPointSize (7);
    myFont.setWeight(QFont::Thin);
    myFont.setFamily(QString::fromUtf8("Trebuchet MS"));
    /* set pen and font to myPen and myFont */
    painter.setPen(myPen);
    painter.setFont(myFont);
    /* Adjust coordinates for text, set to wrap and set rect area */
    QPoint textPoint = coordinate - QPoint(25,-2);
    QRect rect(textPoint,QSize(50,40));
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);
    // Draw Text
    painter.drawText(rect,strToPrint, textOption);
}
