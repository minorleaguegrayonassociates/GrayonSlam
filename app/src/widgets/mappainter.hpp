#pragma once
#include "src/datastore/database.hpp"
#include "airplanepainter.hpp"
#include "beacon.hpp"
#include <QWidget>
#include <QSoundEffect>

class MapPainter : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit MapPainter(QWidget* parent);

    /* Destructor */
    ~MapPainter() override;

    /* setters */
    void setBeaconCoords(int);
    void setDiscoveredEdges(const std::list<Database::completedEdge>&);
    void setDiscoveredEdges(const std::vector<std::pair<std::list<std::pair<int,int>>,int>>&);

    /* Reset */
    void resetMap();

    /* Animations */
    void animateTrip(int stadiumOneId, int stadiumTwoId);
    void animateTrip(const std::pair<std::list<std::pair<int,int>>,int>& tripEdges);
    void animateTrip(std::vector<std::pair<std::list<std::pair<int,int>>,int>>& tripEdges);

private:
    /* Paint Methods */
    void paintStadiums(QPainter& painter, int id, const QPoint& stadiumPoint, const QString& StadiumName);
    void paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2);
    void highlightEdge(QPainter& painter, const QPoint& stadiumCoord1, const QPoint& stadiumCoord2);
    void highlightDiscoveredEdges(QPainter& painter, std::list<Database::completedEdge>& discoveredEdges);
    void highlightDiscoveredEdges(QPainter& painter, std::vector<std::pair<std::list<std::pair<int,int>>,int>>& discoveredEdges);
    void paintText(QPainter& painter, const QPoint& , const QString&);

    /*  Events */
    void paintEvent(QPaintEvent*) override;

    AirplanePainter* m_airplane;
    Beacon* m_beacon;
    Beacon* m_publicBeacon;
    QPoint m_coords;
    std::list<Database::completedEdge> m_discoveredEdgesList;
    std::vector<std::pair<std::list<std::pair<int,int>>,int>> m_discoveredEdgesVector;
    QSoundEffect* effect;
};


