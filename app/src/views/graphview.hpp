#pragma once

#include "view.hpp"
#include "src/widgets/mappainter.hpp"
#include "src/utils/undirected_graph.hpp"

using completedEdge = std::tuple<int,int,int>;

namespace Ui {
class GraphView;
}

class GraphView : public View
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    virtual ~GraphView();
    virtual void resetView();
    virtual void resetUi();

private slots:
    void on_DFSButton_clicked();

    void on_BFSButton_clicked();

    void on_MSTButton_clicked();

private:
    enum class DisplayType
    {
        DFS,
        BFS,
        MST,
        UNSELECTED
    };

    Ui::GraphView *ui;
    MapPainter* m_mapPainter;
    DisplayType m_displayStatus;
    nstd::undirected_graph<int,int> m_graph;
    std::vector<int> m_stadiumIds;
};
