#pragma once
#include "src/views/view.hpp"
#include "src/widgets/navbar.hpp"
#include "src/widgets/souvenirlist.hpp"
#include "src/views/souvenirshop.hpp"
#include "src/views/receiptview.hpp"

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

public slots:
    /* Setter */
    void setReceipt(Qtys&);
    void goToNext();
    void activeTrip();

private:
    Ui::PlanVacationView *m_ui;
    NavBar* m_navbar;
    std::vector<View*> m_vacationViews;
    SouvenirShop* m_souvenirShop;
    ReceiptView* m_receiptViews;
    std::list<int> m_tripList;
    std::vector<Qtys> m_receiptVector;
    int m_previousStadiumId;
    int m_currentStadiumId;
};

