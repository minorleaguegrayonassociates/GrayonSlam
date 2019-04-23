#pragma once

#include <QWidget>

class AirplanePainter : public QWidget
{
    Q_OBJECT
    friend class MapPainter;
public:
    explicit AirplanePainter(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent*) override;
    void setRotation(int startingX, int startingY, int endingX, int endingY);
private:
    double rotate;
    QPixmap m_plane;
};

