#pragma once

#include "view.hpp"
#include "src/widgets/mappainter.hpp"
#include "src/utils/undirected_graph.hpp"

using completedEdge = std::tuple<int,int,int>;

namespace Ui {
class GraphView;
}

/**
 *@class GraphView class
 *
 * This class is used for displaying the information of the graph in the database.
 * It will display the map of the baseball stadiums and perform a dfs, bfs, or mst
 * when a button is clicked. After the action is performed, it will highlight the edges
 * corresponding to the action performed e.g. it will display discovery edges of a bfs
 * if the show bfs button is clicked
 *
 * Note:
 * This view assumes that the database is initialized with data for it to read out of.
 */
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

    void on_LocationsComboBox_currentIndexChanged(int index);

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
