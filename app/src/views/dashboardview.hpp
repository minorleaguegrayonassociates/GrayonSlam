#pragma once
#include "view.hpp"
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

    void resetView() override;
    void resetUi() override;

private:
    /* Splashes */
    static void loadSplashes();
    static std::vector<std::vector<std::string>> splashes;

    Ui::DashboardView* m_ui;
    ImageSlideshow* m_slideshow;
};
