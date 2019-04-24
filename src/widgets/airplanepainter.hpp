#pragma once

#include <QWidget>

class AirplanePainter : public QWidget
{
    Q_OBJECT
public:
    /* Constructor */
    explicit AirplanePainter(QWidget* parent);

    /* events */
    void paintEvent(QPaintEvent*) override;

    /*Setters*/
    void setRotation(int startingX, int startingY, int endingX, int endingY);

private:
    double angleValue;
    QPixmap m_plane;
};

