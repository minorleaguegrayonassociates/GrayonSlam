#pragma once
#include "src/views/view.hpp"
#include "src/widgets/imageslideshow.hpp"

namespace Ui
{
class DashboardView;
}

class DashboardView : public View
{
    Q_OBJECT

public:
    explicit DashboardView(QWidget* parent);
    ~DashboardView() override;

    void resetView() override {}
    void resetUi() override {}

private:
    Ui::DashboardView* m_ui;
    ImageSlideshow* m_slideshow;
};
