#pragma once

#include "view.hpp"
#include "src/widgets/mappainter.hpp"

namespace Ui {
class GraphView;
}

class GraphView : public View
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    virtual ~GraphView();

private:
    Ui::GraphView *ui;
    MapPainter* m_mapPainter;
};
