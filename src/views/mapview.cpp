#include "mapview.hpp"
#include "ui_mapview.h"
#include <QPropertyAnimation>

MapView::MapView(QWidget *parent) :
View(parent),
m_ui(new Ui::MapView)
{
    m_ui->setupUi(this);
    m_map = new MapPainter(m_ui->map_widget);
}

MapView::~MapView()
{
    delete m_ui;
}

/* The resetView function resets the Ui that corresponds with the given view */
void MapView::resetView()
{

}

/* The resetUi function resets the Ui that corresponds with the given view */
void MapView::resetUi()
{

}

void MapView::on_pushButton_clicked()
{
    QPropertyAnimation* animation = new QPropertyAnimation(m_ui->plane, "geometry");
    animation->setDuration(75);
    animation->setStartValue(QRect(QPoint(0,0),m_ui->plane_widget->sizeHint()));
    animation->setEndValue(QRect(QPoint(100,100),m_ui->plane_widget->sizeHint()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
