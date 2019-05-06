#pragma once
#include <QVariantAnimation>
#include "src/widgets/airplanepainter.hpp"

class AirplaneRotationAnimation : public QVariantAnimation
{
    Q_OBJECT
public:
    AirplaneRotationAnimation(AirplanePainter* airplanePainter, QObject* parent = nullptr) : QVariantAnimation(parent), m_airplanePainter(airplanePainter){}
    virtual void updateCurrentValue(const QVariant &value) override;

private:
     AirplanePainter* m_airplanePainter;
};
