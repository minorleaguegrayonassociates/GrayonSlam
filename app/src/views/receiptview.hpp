#pragma once
#include "src/views/view.hpp"
#include "src/widgets/receiptlist.hpp"
#include "src/widgets/souvenirlist.hpp"

namespace Ui {
class ReceiptView;
}

class ReceiptView : public View
{
    Q_OBJECT
public:
    /* Constructor */
    explicit ReceiptView(QWidget* parent);

    /* Destructor */
    ~ReceiptView() override;

    /* Resets */
    void resetView() override;
    void resetUi() override;

    /* Setters */
    void makeReceipt(Qtys&, bool);
    void grandTotal(std::vector<Qtys>&,double);

public slots:

signals:
    void goToNext();

private slots:
    void on_continueToNext_clicked();

private:
    Ui::ReceiptView* m_ui;
    ReceiptList* m_receipt;
};

