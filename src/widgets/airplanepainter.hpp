#pragma once

#include <QWidget>

namespace Ui {
class AirplanePainter;
}

class AirplanePainter : public QWidget
{
    Q_OBJECT
    friend class MapPainter;
public:
    explicit AirplanePainter(QWidget* parent = nullptr);
    ~AirplanePainter() override;
    void paintEvent(QPaintEvent*) override;
    void setRotation(int startingX, int startingY, int endingX, int endingY);
private:
    Ui::AirplanePainter* m_ui;
    double rotate;
    QPixmap m_plane;
};

