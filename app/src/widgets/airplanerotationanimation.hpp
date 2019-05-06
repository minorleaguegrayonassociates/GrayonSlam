#pragma once
#include <QVariantAnimation>
#include "src/widgets/airplanepainter.hpp"

class AirplaneRotationAnimation : public QVariantAnimation
{
    Q_OBJECT
public:
    virtual void updateCurrentValue(const QVariant &value) override;
    AirplaneRotationAnimation(AirplanePainter*, QObject *parent);
private:
     AirplanePainter* aPainter;
};
