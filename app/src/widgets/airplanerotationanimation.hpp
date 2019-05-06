#pragma once
#include <QVariantAnimation>
#include "src/widgets/airplanepainter.hpp"

class AirplaneRotationAnimation : public QVariantAnimation
{
    Q_OBJECT
public:
    /* constructor */
    AirplaneRotationAnimation(AirplanePainter* airplanePainter, QObject* parent = nullptr) : QVariantAnimation(parent), m_airplanePainter(airplanePainter){}
    /* set rotation angle with a q variant */
    virtual void updateCurrentValue(const QVariant &value) override;

private:
     /* airplane to rotate */
     AirplanePainter* m_airplanePainter;
};
