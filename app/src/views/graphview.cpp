#include "graphview.hpp"
#include "ui_graphview.h"

GraphView::GraphView(QWidget *parent) :
    View(parent),
    ui(new Ui::GraphView)
{
    ui->setupUi(this);
    m_mapPainter = new MapPainter(ui->map_widget);
}

GraphView::~GraphView()
{
    delete ui;
}

void GraphView::resetView()
{

}

void GraphView::resetUi()
{

}
