#pragma once
#include <QLabel>
#include <vector>

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
