#include "graphview.hpp"
#include "ui_graphview.h"
#include "src/widgets/beacon.hpp"

/**
 * Constructs a Stadium View with a pointer to the parent widget which it will reside in
 *
 * @param parent pointer to widget it will reside in
 */
GraphView::GraphView(QWidget *parent) :
    View(parent),
    ui(new Ui::GraphView),
    m_displayStatus(DisplayType::UNSELECTED)
{
    ui->setupUi(this);
    m_mapPainter = new MapPainter(ui->map_widget);

    resetView();
}
/**
 * Destructor deletes the Ui and the map painter
 */
GraphView::~GraphView()
{
    delete ui;
    delete m_mapPainter;
}

/**
 * resetView() resets the edge data from the database as well as the stadiums in the
 * combo box. Then it resets the Ui to a map with no highlighted edges.
 */
void GraphView::resetView()
{
    m_displayStatus = DisplayType::UNSELECTED;
    /* add edges to internal graph */
    for(auto edge : Database::getDistances())
    {
        m_graph.addEdge(edge);
    }

    /* add choices to combobox */
    for(auto stadium : Database::getTeamsAndStadiums())
    {
        std::string StadiumName = stadium.second.getName();
        ui->LocationsComboBox->addItem(QString::fromStdString(StadiumName));
        m_stadiumIds.push_back(stadium.second.getId());
    }
    resetUi();
}

/**
 * resetUi() highlights any edges according to the current state of the view
 * For example, if someone presses the DFS button, it will put the view into
 * a DFS state and it will highlight the edges that belong to the DFS.
 *
 * Note: It will use the stadium in the combo box as the starting vertex
 */
void GraphView::resetUi()
{
     m_mapPainter->resetMap();
     int totalMilage;
     std::pair<std::list<completedEdge>,int> returnVal;
     switch(m_displayStatus)
     {
        case DisplayType::DFS:
            returnVal =  m_graph.depthFirstSearch(m_stadiumIds[ui->LocationsComboBox->currentIndex()]);
            m_mapPainter->setDiscoveredEdges(returnVal.first);
            totalMilage = returnVal.second;
            break;

        case DisplayType::BFS:
            returnVal = m_graph.breadthFirstSearch(m_stadiumIds[ui->LocationsComboBox->currentIndex()]);
            m_mapPainter->setDiscoveredEdges(returnVal.first);
            totalMilage = returnVal.second;
            break;

        case DisplayType::MST:
            returnVal = m_graph.primsMST(m_stadiumIds[ui->LocationsComboBox->currentIndex()]);
            m_mapPainter->setDiscoveredEdges(returnVal.first);
            totalMilage = returnVal.second;
            break;

        case DisplayType::UNSELECTED:
            totalMilage = 0;
            break;
     }
     std::string milage = "Total Milage: ";
     milage += std::to_string(totalMilage) + " mi";
     ui->totalMileageLabel->setText(QString::fromStdString(milage));
}

/**
 * on_DFSButton_clicked puts the View into the DFS state and will highlight edges accordingly
 */
void GraphView::on_DFSButton_clicked()
{
    if(ui->LocationsComboBox->currentIndex() != -1)
    {
        m_displayStatus = DisplayType::DFS;
        resetUi();
    }
}

/**
 * on_BFSButton_clicked puts the View into the BFS state and will highlight edges accordingly
 */
void GraphView::on_BFSButton_clicked()
{
    if(ui->LocationsComboBox->currentIndex() != -1)
    {
        m_displayStatus = DisplayType::BFS;
        resetUi();
    }
}

/**
 * on_MSTButton_clicked puts the View into the MST state and will highlight edges accordingly
 */
void GraphView::on_MSTButton_clicked()
{
    if(ui->LocationsComboBox->currentIndex() != -1)
    {
        m_displayStatus = DisplayType::MST;
        resetUi();
    }
}

/**
 * on_LocationsComboBox_currentIndexChanged resets the map's edges when the combobox is changed
 *
 * @param index the index of the current value inside the combobox
 */
void GraphView::on_LocationsComboBox_currentIndexChanged(int index)
{
    if(index != -1)
    {
        m_displayStatus = DisplayType::UNSELECTED;
        resetUi();
    }
}
