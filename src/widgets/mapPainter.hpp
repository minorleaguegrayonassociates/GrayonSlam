#pragma once

#include <QWidget>
#include <map>
namespace Ui {
class graph;
}

class mapPainter : public QWidget
{
Q_OBJECT

public:
explicit mapPainter(QWidget* parent = nullptr);
~mapPainter() override;

void paintEvent(QPaintEvent*) override;

/* setters */
void paintStadiums(QPainter& painter, const QPoint& stadiumPoint, const QString& StadiumName);
void paintEdge(QPainter& painter, const QPoint& stdmCoord1, const QPoint& stdmCoord2, const QString& distance);
void paintText(QPainter& painter, const QPoint& , const QString&);

private:
Ui::graph *m_ui;
std::map<int,QPoint>* m_coordinates;
};


