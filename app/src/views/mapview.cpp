#include "mapview.hpp"
#include "ui_mapview.h"
#include "src/datastore/database.hpp"

/* Constructor */
MapView::MapView(QWidget *parent)
    : View(parent), m_ui(new Ui::MapView)
{
    m_ui->setupUi(this);
    m_mapPainter = new MapPainter(m_ui->map_widget);

    // Set MapState to preview
    setState(MapState::Preview);
}

/* Destructor */
MapView::~MapView()
{
    delete m_ui;
    delete m_mapPainter;
}

/* Resets */
void MapView::resetView()
{
    m_mapPainter->repaint();
    MapView::resetUi();
}

void MapView::resetUi()
{
    m_mapPainter->resetMap();
}

/**
 * Set's the text for the `distanceLabel`
 *
 * @param distance current trip distance
 */
void MapView::setDistance(const QString& distance)
{
    m_ui->distanceLabel->setText(distance);
}

/**
 * This function is in charge of setting setting the state changing
 * the text on the button and showing or hiding the `distanceLabel`
 *
 * @param state either preview state or trip state
 */
void MapView::setState(MapState state)
{
    if(state == MapState::Preview || state == MapState::Trip)
    {
        m_state = state;

        if(m_state == MapState::Preview)
        {
            m_ui->continueToNext->setText(QString("Go Back"));
            m_ui->distanceLabel->setHidden(false);
        }
        else
        {
            m_ui->continueToNext->setText(QString("Continue"));
            m_ui->distanceLabel->setHidden(true);
        }
    }
}

/**
 * Animates a plane between `stadiumFrom` and `stadiumTo`
 *
 * @param stadiumFrom stadium id
 * @param stadiumTo stadium id
 */
void MapView::setAnimation(const int& stadiumFrom,const int& stadiumTo)
{
    m_mapPainter->animateTrip(stadiumFrom,stadiumTo);
}

/**
 * Animates a plane multiple times with a list of edges
 *
 * @param tripEdges
 */
void MapView::setAnimation(const std::pair<std::list<std::pair<int,int>>,int>& tripEdges)
{
    m_mapPainter->animateTrip(tripEdges);
}

/**
 * Animates a whole trip with a vector that can contains multiple lists
 *
 * @param tripEdges
 */
void MapView::setAnimation(std::vector<std::pair<std::list<std::pair<int,int>>,int>>& tripEdges)
{
    m_mapPainter->animateTrip(tripEdges);
}

void MapView::setHighlight(const std::vector<std::pair<std::list<std::pair<int,int>>,int>>& edges)
{
    m_mapPainter->setDiscoveredEdges(edges);
}

void MapView::setHighlight(const std::list<Database::completedEdge>& edges)
{
    m_mapPainter->setDiscoveredEdges(edges);
}

void MapView::on_continueToNext_clicked()
{
    if(m_state == MapState::Preview)
        emit goBackToPlan();
    else
        emit continueToNext();
}
