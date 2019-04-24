#pragma once

#include "src/datastore/database.hpp"
#include "airplanepainter.hpp"
#include "beacon.hpp"
#include <QWidget>

class MapPainter : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit MapPainter(QWidget* parent = nullptr);

    /* Destructor */
    ~MapPainter() override;

    /*  Events */
    void paintEvent(QPaintEvent*) override;

    /* setters */
    void paintStadiums(QPainter& painter, int id, const QPoint& stadiumPoint, const QString& StadiumName);
    void paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2);
    void highlightEdge(QPainter& painter, const QPoint& stadiumCoord1, const QPoint& stadiumCoord2);
    void highlightDiscoveredEdges(QPainter& painter, std::vector<Database::completedEdge>& discoveredEdges);
    void paintText(QPainter& painter, const QPoint& , const QString&);
    void animateTrip(int stadiumOneId, int stadiumTwoId);
    void setDiscoveredVector(std::vector<Database::completedEdge>&);

    /* reset */
    void resetUi();
private:
    AirplanePainter* m_airplane;
    Beacon* m_beacon;
    std::vector<Database::completedEdge>* m_discoveredEdges;
};


