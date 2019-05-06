#include "airplanerotationanimation.hpp"

AirplaneRotationAnimation::AirplaneRotationAnimation(AirplanePainter* airplanePainter, QObject* parent) : QVariantAnimation(parent), m_airplanePainter(airplanePainter){}
void AirplaneRotationAnimation::updateCurrentValue(const QVariant &angle)
{
    bool* ok = new bool;
    double angle2 = angle.toDouble(ok);
    m_airplanePainter->setAngle(angle2);
}
