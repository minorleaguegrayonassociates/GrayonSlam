#pragma once
#include "view.hpp"
#include "src/widgets/mappainter.hpp"

namespace Ui {
class MapView;
}

class MapView : public View
{
    Q_OBJECT

public:
    /* Constructor */
    explicit MapView(QWidget* parent);

    /* Destructor */
    ~MapView() override;

    /* Resets */
    void resetView() override;
    void resetUi() override;

    /* setter */
    void setAnimation(const int&, const int&);
public slots:

signals:
    void goToShop();

private slots:
    void on_goToShop_clicked();

private:
    Ui::MapView* m_ui;
    MapPainter* m_mapPainter;
};

