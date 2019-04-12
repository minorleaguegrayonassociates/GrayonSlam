#pragma once

#include <QWidget>

namespace Ui {
class graph;
}

class graph : public QWidget
{
Q_OBJECT

public:
explicit graph(QWidget* parent = nullptr);
~graph() override;

void paintEvent(QPaintEvent*) override;

/* setters */
void paintStadiums(QPainter& painter, const QPoint& stadiumPoint, const QString& StadiumName);
void paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2, const QString& distance);
void paintText(QPainter& painter, const QPoint& , const QString&);

private:
Ui::graph *m_ui;
};


