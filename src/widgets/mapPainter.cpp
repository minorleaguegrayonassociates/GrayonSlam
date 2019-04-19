#include "map.hpp"
#include "ui_graph.h"
#include <QPainter>
#include <cmath>
#include <QLabel>
#include <QHBoxLayout>
#include "src/datastore/database.hpp"

graph::graph(QWidget *parent)
    : QWidget(parent), m_ui(new Ui::graph)
{
    m_ui->setupUi(this);
    m_coordinates = new std::map<int,QPoint>{
        { 50, QPoint(42,146)},
        { 51, QPoint(79,11)},
        { 52, QPoint(48,163)},
        { 53, QPoint(61,220)},
        { 54, QPoint(88,246)},
        { 55, QPoint(48,205)},
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

    for(auto pair : *m_coordinates)
        paintStadiums(painter, pair.second, QString::fromStdString(Database::findStadiumById(pair.first).getName()));

//    paintText(painter, QPoint(121,205), QString::fromUtf8("Vegas Stadium"));
//    paintText(painter, QPoint(156,254), QString::fromUtf8("Coors Field"));

    painter.end();
}

void graph::paintStadiums(QPainter& painter,const QPoint& stadiumPoint, const QString& stadiumName)
{
    QBrush myBrush;
    myBrush.setColor(Qt::GlobalColor::blue);
    myBrush.setStyle(Qt::BrushStyle::SolidPattern);
    painter.setBrush(myBrush);
    painter.drawEllipse(stadiumPoint, 3, 3);

    paintText(painter, stadiumPoint, stadiumName);
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
