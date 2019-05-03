#pragma once
#include <QLabel>
#include <vector>

/**
 * @class ImageSlideshow class
 *
 * Acts as an animated slideshow for images. Once
 * images are added to the object with @a addImage(),
 * call @a start() on the object to begin the slideshow.
 * The slideshow is pausable as well with @a pause().
 * If a desired interval is wanted for the slideshow,
 * use @a setInterval and pass in the desired milliseconds
 * that each image will show for.
 */
class ImageSlideshow : public QLabel
{
    Q_OBJECT

public:
    /* Constructors */
    explicit ImageSlideshow(QWidget* parent, int msecInterval);

    void addImage(const QPixmap&, Qt::AspectRatioMode = Qt::KeepAspectRatioByExpanding);
    void setInterval(int);

public slots:
    void start();
    void pause();

private slots:
    void loop();

private:
    bool m_play = false;
    int m_msecInterval = 1000;
    unsigned int m_currentIndex = 0;
    std::vector<QPixmap> m_images;
};
