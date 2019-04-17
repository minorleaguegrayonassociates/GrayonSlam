#pragma once
#include "view.hpp"

namespace Ui
{
class AdminView;
}

class AdminView : public View
{
    Q_OBJECT

public:
    explicit AdminView(QWidget* parent);
    ~AdminView() override;

    void resetView() override {}
    void resetUi() override {}

private:
    Ui::AdminView* m_ui;
};
