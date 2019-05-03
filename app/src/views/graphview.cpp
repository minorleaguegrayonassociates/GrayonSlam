#include "graphview.hpp"
#include "ui_graphview.h"

GraphView::GraphView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphView)
{
    ui->setupUi(this);
}

GraphView::~GraphView()
{
    delete ui;
}
