#include "adminview.hpp"
#include "ui_adminview.h"

AdminView::AdminView(QWidget* parent)
    : View(parent), m_ui(new Ui::AdminView)
{
    m_ui->setupUi(this);
}

AdminView::~AdminView()
{
    delete m_ui;
}
