#pragma once
#include <QWidget>

class Beacon : public QWidget
{
    Q_OBJECT
public:
    explicit Beacon(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*) override;
    void hideEvent(QHideEvent*) override;
    void showEvent(QShowEvent*) override;

    void drawBeacon(QPainter& painter, const QPoint& stadiumCoord);
    void setCoords(const QPoint& stadiumCoord);


signals:
public slots:
private:
    QPoint m_coords;
};
