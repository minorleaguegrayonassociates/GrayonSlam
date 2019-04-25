#include "souvenirshop.hpp"
#include "ui_souvenirshop.h"

/* Constructor */
souvenirShop::souvenirShop(QWidget *parent)
    :View(parent), m_ui(new Ui::souvenirShop)
{
    m_ui->setupUi(this);
}

/* Destructor */
souvenirShop::~souvenirShop()
{
    delete m_ui;
}

/* Resets */
void souvenirShop::resetView()
{}

void souvenirShop::resetUi()
{}
