#include "graph.hpp"
#include "ui_graph.h"
#include <QPainter>
#include <cmath>
#include <QLabel>
#include <QHBoxLayout>

graph::graph(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::graph)
{
    m_ui->setupUi(this);
    m_coordinates = new std::map<int,QPoint>{
        { 51, QPoint(79,11)},
    };
}

graph::~graph()
{
    delete m_ui;
}

void graph::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);

    paintText(painter, (*m_coordinates)[0], QString::fromUtf8("Safeco Park"));
    paintText(painter, QPoint(42,146), QString::fromUtf8("AT&T Park"));
    paintText(painter, QPoint(48,163), QString::fromUtf8("Oakland–Alameda County Coliseum"));
    paintText(painter, QPoint(48,205), QString::fromUtf8("Dodger Stadium"));
    paintText(painter, QPoint(61,220), QString::fromUtf8("Angel Stadium of Anaheim"));
    paintText(painter, QPoint(88,246), QString::fromUtf8("Petco Park"));
    paintText(painter, QPoint(121,205), QString::fromUtf8("Vegas Stadium"));
    paintText(painter, QPoint(156,254), QString::fromUtf8("Coors Field"));

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
    font.setPointSize (7);
    font.setWeight(QFont::Thin);
    font.setFamily(QString::fromUtf8("Trebuchet MS"));

    painter.setPen(myPen);
    painter.setFont(font);
    QPoint textPoint = coords - QPoint(42,0);
    QRect rect(textPoint,QSize(54,41));
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);
    painter.drawText(rect,strToPrint, textOption);
}
