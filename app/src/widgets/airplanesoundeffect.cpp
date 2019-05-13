#include "airplanesoundeffect.hpp"

void airplaneSoundEffect::updateCurrentValue(const QVariant&)
{
    m_effect = new QSoundEffect;
    m_effect->setSource(QUrl::fromLocalFile("airplane.wav"));
    m_effect->setLoopCount(1);
    m_effect->setVolume(.5);
    m_effect->play();
}
