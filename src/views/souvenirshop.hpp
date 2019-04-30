#pragma once
#include "src/views/view.hpp"
#include "src/widgets/souvenirlist.hpp"
#include <QMessageBox>

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

public slots:

signals:
    void goToReceipt(Qtys&);
    void goToNext();

private slots:
    void on_next_clicked();
    void on_checkout_clicked();
    void on_removeItem_clicked();
    void on_addToCart_clicked();
    void updateQty();

private:
    /* Private setters */
    void updateCurrentTrip();
    QMessageBox::StandardButton promptToContinue();

    Ui::SouvenirShop* m_ui;
    SouvenirList* m_vacationSouvenirList;
    SouvenirList* m_vacationSouvenirCart;
    int m_currentStadiumId;
    int m_currentTeamId;
};

