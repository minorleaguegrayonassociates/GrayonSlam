#include "graphview.hpp"
#include "ui_graphview.h"

GraphView::GraphView(QWidget *parent) :
    View(parent),
    ui(new Ui::GraphView),
    m_displayStatus(DisplayType::UNSELECTED)
{
    ui->setupUi(this);
    m_mapPainter = new MapPainter(ui->map_widget);

    resetView();
}

GraphView::~GraphView()
{
    delete ui;
    delete m_mapPainter;
}

void GraphView::resetView()
{
    resetUi();
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

}

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

void GraphView::on_DFSButton_clicked()
{
    if(ui->LocationsComboBox->currentIndex() != -1)
    {
        m_displayStatus = DisplayType::DFS;
        resetUi();
    }
}

void GraphView::on_BFSButton_clicked()
{
    if(ui->LocationsComboBox->currentIndex() != -1)
    {
        m_displayStatus = DisplayType::BFS;
        resetUi();
    }
}

void GraphView::on_MSTButton_clicked()
{
    if(ui->LocationsComboBox->currentIndex() != -1)
    {
        m_displayStatus = DisplayType::MST;
        resetUi();
    }
}
