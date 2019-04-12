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
void paintStadiums(QPainter& painter, QPoint& stadiumPoint, QString& StadiumName);
void paintEdge(QPainter& painter,QPoint& stdmCoord1, QPoint& stdmCoord2,QString distance);
void paintText(QPainter& painter, QPoint& ,QString&);
private:
Ui::graph *m_ui;
};


