#include "imageslideshow.hpp"
#include <QTimer>

/**
 * Constructs a slideshow in @a parent with a timer interval
 * of @a msecInterval milliseconds.
 *
 * @param parent Parent widget
 * @param msecInterval Interval of images in milliseconds
 */
ImageSlideshow::ImageSlideshow(QWidget* parent, int msecInterval)
    : QLabel(parent), m_msecInterval(msecInterval)
{
    resize(parent->size());
}

/**
 * Adds an image to the slideshow. If the image is null,
 * this function does nothing.
 *
 * @param image Image to add to the slideshow
 */
void ImageSlideshow::addImage(const QPixmap& image, Qt::AspectRatioMode mode)
{
    if(image.isNull())
        return;

    QPixmap copy = image.scaled(size(), mode);
    m_images.push_back(copy);
}

/**
 * Starts the slideshow. If no images have been added,
 * this function does nothing.
 */
void ImageSlideshow::start()
{
    if(m_images.empty())
        return;

    m_play = true;
    loop();
}

/**
 * Pauses the slideshow.
 */
void ImageSlideshow::pause()
{
    m_play = false;
}

/**
 * Displays the next image in the slideshow and calls
 * itself. If @a pause has been called, this function
 * does nothing.
 */
void ImageSlideshow::loop()
{
    if(!m_play)
        return;

    setPixmap(m_images[m_currentIndex]);

    m_currentIndex = (m_currentIndex + 1) % m_images.size();

    QTimer::singleShot(m_msecInterval, this, &ImageSlideshow::loop);
}
