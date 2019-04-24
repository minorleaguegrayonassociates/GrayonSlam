#pragma once
#include <QLabel>
#include <vector>

class ImageSlideshow : public QLabel
{
    Q_OBJECT

public:
    /* Constructors */
    ImageSlideshow(QWidget* parent, int msecInterval);

    void addImage(const QPixmap&);
    void setInterval(int);

public slots:
    void play();
    void stop();

private slots:
    void loop();

private:
    bool m_play = false;
    int m_msecInterval = 1000;
    unsigned int m_currentIndex = 0;
    std::vector<QPixmap> m_images;
};
