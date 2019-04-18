#include "stadiumview.hpp"
#include "ui_stadiumview.h"

StadiumView::StadiumView(QWidget *parent) :
    View(parent),
    ui(new Ui::StadiumView)
{
    ui->setupUi(this);
}

StadiumView::~StadiumView()
{
    delete ui;
}
