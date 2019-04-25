#pragma once
#include <QWidget>
#include "src/views/view.hpp"

namespace Ui {
class souvenirShop;
}

class souvenirShop : public View
{
    Q_OBJECT

public:
    /* Constructor */
    explicit souvenirShop(QWidget* parent);

    /* Destructor */
    ~souvenirShop() override;

    /* Resets */
    void resetView() override;
    void resetUi() override;

private:
    Ui::souvenirShop* m_ui;
};

