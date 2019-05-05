#pragma once

#include "view.hpp"
#include "src/widgets/mappainter.hpp"
#include "src/utils/undirected_graph.hpp"

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
    /* Constructor */
    explicit GraphView(QWidget* parent);

    /* Destructor */
    virtual ~GraphView() override;

    /* Resets */
    virtual void resetView() override;
    virtual void resetUi() override;

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

    /* Setters */
    void setDisplayStatus(DisplayType);

    /* Data Members*/
    Ui::GraphView *ui;
    MapPainter* m_mapPainter;
    DisplayType m_displayStatus;
    nstd::undirected_graph<int,int> m_graph;
    std::vector<int> m_stadiumIds;
};
