#include "mappainter.hpp"
#include "ui_mappainter.h"
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

MapPainter::MapPainter(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::MapPainter)
{
    m_ui->setupUi(this);
    m_coords = Database::getCoordinates();
}

MapPainter::~MapPainter()
{
    delete m_ui;
}

void MapPainter::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);

    for(auto pair : Database::getCoordinates())
        paintStadiums(painter, pair.first,QPoint(pair.second.first,pair.second.second), QString::fromStdString(Database::findStadiumById(pair.first).getName()));

    painter.end();
}

void MapPainter::paintStadiums(QPainter& painter,int id, const QPoint& stadiumPoint, const QString& stadiumName)
{
    QBrush myBrush;
     QPen myPen;
     if(Database::findTeamById(id).league == Team::League::NATIONAL)
    {
        myBrush.setColor(Qt::GlobalColor::blue);
        myPen.setColor(Qt::GlobalColor::blue);
    }
    else
    {
        myBrush.setColor(Qt::GlobalColor::red);
        myPen.setColor(Qt::GlobalColor::red);
    }
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    painter.setPen(myPen);
    myBrush.setStyle(Qt::BrushStyle::SolidPattern);
    painter.setBrush(myBrush);
    painter.drawEllipse(stadiumPoint, 2, 2);
    paintText(painter, stadiumPoint, stadiumName);
}

void MapPainter::paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2, const QString& distance)
{
    QPen myPen;
    myPen.setColor(Qt::GlobalColor::red);
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    painter.setPen(myPen);

    QPoint one = stdmCoord1 + QPoint(1,1);
    QPoint two = stdmCoord2 - QPoint(1,1);
    painter.drawLine(one, two);

    QPoint midPoint = (one-two)/2;
    paintText(painter, midPoint, distance);
}

void MapPainter::paintText(QPainter& painter, const QPoint& coords, const QString& strToPrint)
{
    QPen myPen;

    myPen.setWidth(1);
    myPen.setColor(Qt::GlobalColor::black);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);

    QFont font=painter.font() ;
    font.setPointSize (7);
    font.setWeight(QFont::Thin);
    font.setFamily(QString::fromUtf8("Trebuchet MS"));

    painter.setPen(myPen);
    painter.setFont(font);
    QPoint textPoint = coords - QPoint(30,0);
    QRect rect(textPoint,QSize(54,41));
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);
    painter.drawText(rect,strToPrint, textOption);
}
