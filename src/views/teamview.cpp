#include "teamview.hpp"
#include "ui_teamview.h"

TeamView::TeamView(QWidget *parent) :
    AbstractViewModel(parent),
    ui(new Ui::TeamView)
{
    ui->setupUi(this);
}

TeamView::~TeamView()
{
    delete ui;
}

void TeamView::resetView()
{
    //To be implemented with data
}

void TeamView::resetUI()
{
    //To be implemented with data
}
