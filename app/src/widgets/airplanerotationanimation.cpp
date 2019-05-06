#include "airplanerotationanimation.hpp"

/**
 * updateCurrentValue is a function called during the animation to continually update the angle.
 * All qvariantanimation must overload this to define the behavior of the animation
 *
 * @param angle angle at which the plane gets updated to
 */
void AirplaneRotationAnimation::updateCurrentValue(const QVariant& angle)
{
    bool* ok = new bool;
    double angle2 = angle.toDouble(ok);
    m_airplanePainter->setAngle(angle2);
}
