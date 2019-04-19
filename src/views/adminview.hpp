#pragma once
#include "view.hpp"
#include "src/widgets/souvenirlist.hpp"

namespace Ui
{
class AdminView;
}

class AdminView : public View
{
    Q_OBJECT

public:
    /* Constructors */
    explicit AdminView(QWidget* parent);

    /* Destructor */
    ~AdminView() override;

    /* Resets */
    void resetView() override;
    void resetUi() override;

private slots:
    void loadSouvenirLists(int stadiumId);

    /* Stadium subview controls */
    void fillStadiumEditFields(int stadiumId);

    /* Souvenir subview controls */
//    void fillSouvenirEditFields(int souvenirId);
    void on_pushButton_souvGoBack_clicked();

private:
    Ui::AdminView* m_ui;
    int m_currentStadiumId = -1;

    /* Widgets */
    SouvenirList* m_availableSouvenirList;
    SouvenirList* m_hiddenSouvenirList;
};
