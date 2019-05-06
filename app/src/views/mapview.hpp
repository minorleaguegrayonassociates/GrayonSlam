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
    enum class MapState{ Preview, Trip };

    /* Constructor */
    explicit MapView(QWidget* parent);

    /* Destructor */
    ~MapView() override;

    /* Resets */
    void resetView() override;
    void resetUi() override;

    /* setter */
    void setState(MapState);
    void setAnimation(const int&, const int&);
    void setAnimation(const std::pair<std::list<std::pair<int,int>>,int>& tripEdges);
    void setAnimation(std::vector<std::pair<std::list<std::pair<int,int>>,int>>& tripEdges);
    void setHighlight(const std::vector<std::pair<std::list<std::pair<int,int>>,int>>&);
    void setHighlight(const std::list<Database::completedEdge>&);

public slots:

signals:
    void continueToNext();
    void goBackToPlan();

private slots:
    void on_continueToNext_clicked();

private:
    Ui::MapView* m_ui;
    MapPainter* m_mapPainter;
    MapState m_state;
};

