#pragma once

#include <QWidget>
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
    explicit MapView(QWidget *parent = nullptr);

    /* Destructor */
    ~MapView() override;

    /* The resetView function resets the Ui that corresponds with the given view */
    void resetView() override;

    /* The resetUi function resets the Ui that corresponds with the given view */
    void resetUi() override;

private:
    Ui::MapView* m_ui;
    MapPainter* m_mapPainter;
};


