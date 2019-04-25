#include "planvacationview.hpp"
#include "ui_planvacationview.h"

/* Constructor */
PlanVacationView::PlanVacationView(QWidget *parent, NavBar* bar)
    : View(parent), m_ui(new Ui::PlanVacationView), m_navbar(bar)
{
    m_ui->setupUi(this);
}

/* Destructor */
PlanVacationView::~PlanVacationView()
{
    delete m_ui;
    delete m_navbar;

    //Delete each vacationView
    std::for_each(m_vacationViews.begin(), m_vacationViews.end(),
                  [](View* view){delete view;});
}

/* Resets */
void PlanVacationView::resetView()
{}

void PlanVacationView::resetUi()
{}
