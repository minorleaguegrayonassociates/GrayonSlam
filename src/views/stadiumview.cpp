#include "stadiumview.hpp"
#include "ui_stadiumview.h"

StadiumView::StadiumView(QWidget *parent) :
    View(parent),
    ui(new Ui::StadiumView)
{
    ui->setupUi(this);

    m_stadiumList = new StadiumList(ui->stadiumList);

}

StadiumView::~StadiumView()
{
    delete ui;
    delete m_stadiumList;
}

void StadiumView::resetView()
{
    //clear all data, get it new from database, and populate table
}

void StadiumView::resetUI()
{
    //clear table and repopulate it with list
}
