#include "teamview.hpp"
#include "ui_teamview.h"

TeamView::TeamView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamView)
{
    ui->setupUi(this);
}

TeamView::~TeamView()
{
    delete ui;
}
