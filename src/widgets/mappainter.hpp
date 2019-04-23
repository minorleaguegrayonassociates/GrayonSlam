#pragma once

#include "src/datastore/database.hpp"
#include "airplanepainter.hpp"
#include <QWidget>
#include <map>

namespace Ui {
class MapPainter;
}

class MapPainter : public QWidget
{
Q_OBJECT

public:
explicit MapPainter(QWidget* parent = nullptr);
~MapPainter() override;

void paintEvent(QPaintEvent*) override;

/* setters */
void paintStadiums(QPainter& painter, int id, const QPoint& stadiumPoint, const QString& StadiumName);
void paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2);
void highlightEdge(QPainter& painter, const QPoint& stadiumCoord1, const QPoint& stadiumCoord2);
void paintText(QPainter& painter, const QPoint& , const QString&);
void animateTrip(int stadiumOneId, int stadiumTwoId);

private:
Ui::MapPainter* m_ui;
AirplanePainter* m_airplane;
};


