#pragma once
#include <QWidget>

class Beacon : public QWidget
{
    Q_OBJECT
public:
    /* Constructor */
    explicit Beacon(QWidget* parent);

    /* setters */
    void setCoords(const QPoint& stadiumCoord);

    /* Static Variable */
    static const QPoint outerBound;

private:
    /* Paint Method */
    void drawBeacon(QPainter& painter, const QPoint& stadiumCoord);

    /* Events */
    void paintEvent(QPaintEvent*) override;
    void hideEvent(QHideEvent*) override;
    void showEvent(QShowEvent*) override;

    QPoint m_coords;
};
