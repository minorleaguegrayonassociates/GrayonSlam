#pragma once
#include <QWidget>

class Beacon : public QWidget
{
    Q_OBJECT
public:
    /* Constructor */
    explicit Beacon(QWidget *parent = nullptr);

    /* Events */
    void paintEvent(QPaintEvent*) override;
    void hideEvent(QHideEvent*) override;
    void showEvent(QShowEvent*) override;

    /* setters */
    void drawBeacon(QPainter& painter, const QPoint& stadiumCoord);
    void setCoords(const QPoint& stadiumCoord);

private:
    QPoint m_coords;
};
