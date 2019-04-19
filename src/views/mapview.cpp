#include "mapview.hpp"
#include "ui_mapview.h"

MapView::MapView(QWidget *parent) :
View(parent),
m_ui(new Ui::MapView)
{
m_ui->setupUi(this);
}

MapView::~MapView()
{
delete m_ui;
}

/* The resetView function resets the Ui that corresponds with the given view */
void resetView()
{

}

/* The resetUi function resets the Ui that corresponds with the given view */
void resetUi()
{

}
