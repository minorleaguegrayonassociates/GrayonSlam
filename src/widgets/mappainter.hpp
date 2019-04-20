#pragma once

#include "src/datastore/database.hpp"
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
void paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2, const QString& distance);
void paintText(QPainter& painter, const QPoint& , const QString&);

private:
Ui::MapPainter *m_ui;
Database::coords m_coords;
};


