#pragma once
#include <QVariantAnimation>
#include <QSoundEffect>


class airplaneSoundEffect : public QVariantAnimation
{
    Q_OBJECT
public:
    airplaneSoundEffect(QObject* parent = nullptr) : QVariantAnimation(parent){}

    /* set the volume with a q variant */
    virtual void updateCurrentValue(const QVariant &value) override;

private:
    QSoundEffect* m_effect;
};

