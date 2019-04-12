#include "graph.hpp"
#include "ui_graph.h"
#include <QPainter>
#include <cmath>

graph::graph(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::graph)
{
    m_ui->setupUi(this);
}

graph::~graph()
{
    delete m_ui;
}

void graph::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);

//    painter.drawEllipse(QRect(48, 163, 5, 5));
//    painter.drawEllipse(QRect(56, 205, 5, 5));
//    painter.drawEllipse(QRect(73, 220, 5, 5));
//    painter.drawEllipse(QRect(84, 246, 5, 5));
//    painter.drawEllipse(QRect(121, 201, 5, 5));
//    painter.drawEllipse(QRect(150, 253, 5, 5));
//    painter.drawEllipse(QRect(79, 11, 5, 5));
//    painter.drawEllipse(QRect(254, 159, 5, 5));

    paintStadiums(painter, QPoint(79,11), QString::fromUtf8("Safeco Park"));
    paintStadiums(painter, QPoint(35,146), QString::fromUtf8("AT&T Park"));
    paintEdge(painter, QPoint(79,11), QPoint(35,146), QString::fromUtf8("680 mi"));
    painter.end();
}

void graph::paintStadiums(QPainter& painter,const QPoint& stadiumPoint, const QString& stadiumName)
{
    QBrush myBrush;
    myBrush.setColor(Qt::GlobalColor::blue);
    myBrush.setStyle(Qt::BrushStyle::SolidPattern);
    painter.setBrush(myBrush);
    painter.drawEllipse(stadiumPoint, 3, 3);

    QPoint forText =  stadiumPoint+QPoint(5,0);
    paintText(painter, forText, stadiumName);
}

void graph::paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2, const QString& distance)
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

void graph::paintText(QPainter& painter, const QPoint& coords, const QString& strToPrint)
{
    QPen myPen;

    myPen.setWidth(1);
    myPen.setColor(Qt::GlobalColor::black);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);


    QFont font=painter.font() ;
    font.setPointSize (10);
    font.setWeight(QFont::Light);
    font.setFamily(QString::fromUtf8("Monospace"));

    painter.setPen(myPen);
    painter.setFont(font);

    painter.drawText(coords, strToPrint);
}
