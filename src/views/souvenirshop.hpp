#pragma once
#include <QWidget>
#include "src/views/view.hpp"
#include "src/widgets/souvenirlist.hpp"

namespace Ui {
class SouvenirShop;
}

class SouvenirShop : public View
{
    Q_OBJECT

public:
    /* Constructor */
    explicit SouvenirShop(QWidget* parent);

    /* Destructor */
    ~SouvenirShop() override;

    /* Setters */
    void setCurrentStadiumId(int);

    /* Resets */
    void resetView() override;
    void resetUi() override;

private slots:
    void on_addToCart_clicked();
    void on_removeItem_clicked();

private:
    /* Private setters */
    void updateCurrentTrip();

    Ui::SouvenirShop* m_ui;
    SouvenirList* m_vacationSouvenirList;
    SouvenirList* m_vacationSouvenirCart;
    int m_currentStadiumId;
    int m_currentTeamId;
};
