#pragma once

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
    void paintText(QPainter& painter, const QPoint& , const QString&);
    void animateTrip(int stadiumOneId, int stadiumTwoId);

private:
    AirplanePainter* m_airplane;
    Beacon* m_beacon;
};


