#pragma once
#include <QWidget>

class AirplanePainter : public QWidget
{
    Q_OBJECT
public:
    /* Constructor */
    explicit AirplanePainter(QWidget* parent);

    /*Setters*/
    void setRotation(int startingX, int startingY, int endingX, int endingY);
    void setAngle(double angle);
    double getAngle();

    /* Static Variable */
    static const QSize planeSize;

private:
    /* events */
    void paintEvent(QPaintEvent*) override;

    double angleValue;
    QPixmap m_plane;
};

