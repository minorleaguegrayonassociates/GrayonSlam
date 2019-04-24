#include "imageslideshow.hpp"
#include <QTimer>

ImageSlideshow::ImageSlideshow(QWidget* parent, int msecInterval)
    : QLabel(parent), m_msecInterval(msecInterval)
{
    resize(parent->size());
}

void ImageSlideshow::addImage(const QPixmap& image)
{
    m_images.push_back(image);
}

void ImageSlideshow::play()
{
    m_play = true;
    loop();
}

void ImageSlideshow::stop()
{
    m_play = false;
}

void ImageSlideshow::loop()
{
    if(!m_play || m_images.empty())
        return;

    setPixmap(m_images[m_currentIndex]);

    m_currentIndex = (m_currentIndex + 1) % m_images.size();

    QTimer::singleShot(m_msecInterval, this, &ImageSlideshow::loop);
}
