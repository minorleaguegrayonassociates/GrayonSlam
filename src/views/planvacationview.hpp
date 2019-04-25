#pragma once
#include "src/views/view.hpp"
#include "src/widgets/navbar.hpp"

namespace Ui {
class PlanVacationView;
}

class PlanVacationView : public View
{
    Q_OBJECT
public:
    /* Constructor */
    PlanVacationView(QWidget* parent, NavBar* m_navbar);

    /* Destructor */
    ~PlanVacationView() override;

    /* Resets */
    void resetView() override;
    void resetUi() override;

private:
    Ui::PlanVacationView *m_ui;
    NavBar* m_navbar;
    std::vector<View*> m_vacationViews;
};

