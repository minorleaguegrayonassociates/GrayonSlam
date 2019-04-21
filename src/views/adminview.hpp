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
    void fillStadiumList();
    void fillSouvenirLists(StadiumId);
    SouvenirId getCurrentSouvenirId() const;

    /* Stadium subview controls */
    void fillStadiumEditFields(StadiumId);
    void on_pushButton_stadEditSouvenirs_clicked();

    /* Souvenir subview controls */
    void fillSouvenirEditFields(SouvenirId);
    void on_pushButton_souvConfirmEdit_clicked();
    void on_pushButton_souvConfirmAdd_clicked();
    void on_pushButton_souvReturn_clicked();

private:
    Ui::AdminView* m_ui;
    StadiumId m_currentStadiumId = -1;

    /* Widgets */
    SouvenirList* m_availableSouvenirList;
    SouvenirList* m_hiddenSouvenirList;
};
