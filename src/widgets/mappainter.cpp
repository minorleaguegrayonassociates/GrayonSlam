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
}

MapPainter::~MapPainter()
{
    delete m_ui;
}

void MapPainter::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    std::map<int,Database::coords> tempCoords(Database::getCoordinates());
    for(auto edge : Database::getDistances())
        paintEdge(painter,QPoint(tempCoords.find(std::get<0>(edge))->second.first,
                                  tempCoords.find(std::get<0>(edge))->second.second),
                          QPoint(tempCoords.find(std::get<1>(edge))->second.first,
                                  tempCoords.find(std::get<1>(edge))->second.second));

    for(auto pair : tempCoords)
        paintStadiums(painter, pair.first,QPoint(pair.second.first,pair.second.second), QString::fromStdString(Database::findStadiumById(pair.first).getName()));

    painter.end();
}

void MapPainter::paintStadiums(QPainter& painter,int id, const QPoint& stadiumPoint, const QString& stadiumName)
{
    QBrush myBrush;
    QPen myPen;
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
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    painter.setPen(myPen);
    myBrush.setStyle(Qt::BrushStyle::SolidPattern);
    painter.setBrush(myBrush);
    painter.drawEllipse(stadiumPoint, 1, 1);
    paintText(painter, stadiumPoint, stadiumName);
}

void MapPainter::paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2)
{
    QPen myPen;
    myPen.setColor(Qt::GlobalColor::black);
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::DotLine);
    painter.setPen(myPen);

    QPoint one = stdmCoord1 + QPoint(1,1);
    QPoint two = stdmCoord2 - QPoint(1,1);
    painter.drawLine(one, two);
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
    QPoint textPoint = coords - QPoint(25,-2);
    QRect rect(textPoint,QSize(50,40));
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);
    painter.drawText(rect,strToPrint, textOption);
}
