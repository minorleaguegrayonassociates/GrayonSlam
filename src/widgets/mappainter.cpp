#include "mappainter.hpp"
#include <QPainter>
#include <QPropertyAnimation>

// Adjust given coordinates by these coordinates before printing stadium names
const QPoint textAdjustment(25,-2);
// Size of rectangle that hold text
const QSize textRect(50,40);

/* Constuctor */
MapPainter::MapPainter(QWidget* parent)
    : QWidget(parent)
{
    resize(parent->size());

    /* Make an instance of an AirplanePainter with MapPainter as it's parent and set it's size */
    m_airplane = new AirplanePainter(this);
    m_airplane->resize(AirplanePainter::planeSize);

    /* Making an instance of Beacon - signals `To` location when animating */
    m_beacon = new Beacon(this);
}

/* Destuctor */
MapPainter::~MapPainter()
{
    delete m_airplane;
    delete m_beacon;
}

/**
 * Draws stadium and it's name at the given coordinate
 *
 * @param painter QPainter
 * @param id stadium id - used to find it's team league and draw the correct color
 * @param stadiumCoordinate QPoint - x, y coordinates where the stadium and text will be drawn
 * @param stadiumName QString name of stadium, will be drawn at the coordinate provided
 */
void MapPainter::paintStadiums(QPainter& painter,int id, const QPoint& stadiumCoordinate, const QString& stadiumName)
{
    QBrush myBrush;
    QPen myPen;

    /* If the leage is National set pen and brush blue, else set them red */
    if(Database::findTeamById(Database::findStadiumById(id).getTeamId()).league == Team::League::NATIONAL)
    {
        myBrush.setColor(Qt::GlobalColor::blue);
        myPen.setColor(Qt::GlobalColor::blue);
    }
    else
    {
        myBrush.setColor(Qt::GlobalColor::red);
        myPen.setColor(Qt::GlobalColor::red);
    }
    /* set myPen info */
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::SolidLine);

    //set brush style
    myBrush.setStyle(Qt::BrushStyle::SolidPattern);

    /* set painters pen and brush to myPen and myBrush */
    painter.setBrush(myBrush);
    painter.setPen(myPen);

    // Draw stadium
    painter.drawEllipse(stadiumCoordinate, 1, 1);

    // Draw stadium name
    paintText(painter, stadiumCoordinate, stadiumName);
}

/**
 * Draws dotted line between the coordinates provided
 *
 * @param painter QPainter
 * @param stadiumCoord1 QPoint - x, y coordinates where the line where start
 * @param stadiumCoord2 QPoint - x, y coordinates where the line will end
 */
void MapPainter::paintEdge(QPainter& painter, const QPoint& stadiumCoord1, const QPoint& stadiumCoord2)
{
    QPen myPen;

    /* set myPen info */
    myPen.setColor(Qt::GlobalColor::black);
    myPen.setWidth(1);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);
    myPen.setStyle(Qt::PenStyle::DotLine);

    // set pen myPen
    painter.setPen(myPen);

    /* adjust line so it sits a bit closer to the center of the stadium circle */
    QPoint one = stadiumCoord1 + QPoint(1,1);
    QPoint two = stadiumCoord2 - QPoint(1,1);

    // Draw Line
    painter.drawLine(one, two);
}

/**
 * highlights lines between the edge provided
 *
 * @param painter QPainter
 * @param stadiumCoord1 QPoint - x, y coordinates where the line where start
 * @param stadiumCoord2 QPoint - x, y coordinates where the line will end
 */
void MapPainter::highlightEdge(QPainter& painter, const QPoint& stadiumCoord1, const QPoint& stadiumCoord2)
{
    QPen myPen;
    /* set myPen info */
    myPen.setColor(Qt::GlobalColor::yellow);
    myPen.setWidth(6);
    myPen.setCapStyle(Qt::PenCapStyle::RoundCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
    myPen.setStyle(Qt::PenStyle::SolidLine);

    // set pen myPen
    painter.setPen(myPen);

    /* adjust line so it sits a bit closer to the center of the stadium circle */
    QPoint one = stadiumCoord1 + QPoint(1,1);
    QPoint two = stadiumCoord2 - QPoint(1,1);

    // Draw Line
    painter.drawLine(one, two);
}

/**
 * highlights lines between the container of edges provided
 * made to highlight a trips discovered edges
 *
 * @param painter QPainter
 * @param discoveredEdges vector of completedEdges [tuple(stadiumId,stadiumId,weight)]
 */
void MapPainter::highlightDiscoveredEdges(QPainter& painter, std::vector<Database::completedEdge>& discoveredEdges)
{
     std::map<int,Database::coords> coords(Database::getCoordinates());
    for(auto edge: discoveredEdges)
    {
        highlightEdge(painter, QPoint(coords.find(std::get<0>(edge))->second.first,
                                      coords.find(std::get<0>(edge))->second.second),
                               QPoint(coords.find(std::get<1>(edge))->second.first,
                                      coords.find(std::get<1>(edge))->second.second));
    }
}

/**
 * Draws text at the coordinates provided
 *
 * @param painter QPainter
 * @param coordinate QPoint - x, y coordinates where text will be printed
 * @param strToPrint QString that will be printed
 */
void MapPainter::paintText(QPainter& painter, const QPoint& coordinate, const QString& strToPrint)
{
    QPen myPen;

    /* set pen info */
    myPen.setWidth(1);
    myPen.setColor(Qt::GlobalColor::black);
    myPen.setStyle(Qt::PenStyle::SolidLine);
    myPen.setCapStyle(Qt::PenCapStyle::FlatCap);
    myPen.setJoinStyle(Qt::PenJoinStyle::MPenJoinStyle);

    /* set font info */
    QFont myFont=painter.font() ;
    myFont.setPointSize (7);
    myFont.setWeight(QFont::Thin);
    myFont.setFamily(QString::fromUtf8("Trebuchet MS"));

    /* set pen and font to myPen and myFont */
    painter.setPen(myPen);
    painter.setFont(myFont);

    /* Adjust coordinates for text, set to wrap and set rect area */
    QPoint textPoint = coordinate - textAdjustment;
    QRect rect(textPoint,textRect);
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WordWrap);

    // Draw Text
    painter.drawText(rect,strToPrint, textOption);
}

/*
 * Takes From and To stadium id's animates a plane starting at
 * froms coordinates and ending at to coordinates
 *
 * @param stadiumOneId From: id
 * @param stadiumTwoId To: id
*/
void MapPainter::animateTrip(int stadiumOneId, int stadiumTwoId)
{
    // Always set airplane visable before use
    m_airplane->setHidden(false);

    // Getting the coordinates of all the stadiums
    std::map<int,Database::coords> tempCoords(Database::getCoordinates());

    // Insert coordinates to calculate the planes angle
    m_airplane->setRotation(tempCoords[stadiumOneId].first,tempCoords[stadiumOneId].second,
                            tempCoords[stadiumTwoId].first,tempCoords[stadiumTwoId].second);

    // Set beacon at `to` location, stadiumTwo
    m_beacon->setCoords(QPoint(tempCoords[stadiumTwoId].first,tempCoords[stadiumTwoId].second));

    /* setting up m_airplane to animate between two stadium coordinates */
    QPropertyAnimation* animation = new QPropertyAnimation(m_airplane, "geometry");
    animation->setDuration(600);
    animation->setStartValue(QRect(QPoint(tempCoords[stadiumOneId].first-m_airplane->size().width()/2,
                                          tempCoords[stadiumOneId].second-m_airplane->size().height()/2),
                                          m_airplane->size()));
    animation->setEndValue(QRect(QPoint(tempCoords[stadiumTwoId].first-m_airplane->size().width()/2,
                                        tempCoords[stadiumTwoId].second-m_airplane->size().height()/2),
                                        m_airplane->size()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

/**
 * Set's distcoveredEdges vector so that the
 * painter can highlight the discovered path
 *
 * @param discoveredEdges vector of completed edges
 */
void MapPainter::setDiscoveredVector(const std::vector<Database::completedEdge>& discoveredEdges)
{
    m_discoveredEdges = discoveredEdges;
}

/**
 * @brief set's airplane and beacon so that they're out of site of the MapView when a user enter's the view
 */
void MapPainter::resetMap()
{
    // Set to hidden
    m_airplane->setHidden(true);
    // Set coordinates outside of widget coordinates
    m_beacon->setCoords(Beacon::outerBound);

    if(!m_discoveredEdges.empty())
        m_discoveredEdges.clear();
}

/**
 * @brief Draws all stadiums and all the edges between the stadiums
 */
void MapPainter::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    std::map<int,Database::coords> tempCoords(Database::getCoordinates());

    /* If m_discoverEdges is populated with edges, highlight discovered edges */
    if(!m_discoveredEdges.empty())
    {
        highlightDiscoveredEdges(painter, m_discoveredEdges);
    }

    /* Paint edge between stadiums */
    for(auto edge : Database::getDistances())
    {
        paintEdge(painter,QPoint(tempCoords.find(std::get<0>(edge))->second.first,
                                 tempCoords.find(std::get<0>(edge))->second.second),
                          QPoint(tempCoords.find(std::get<1>(edge))->second.first,
                                 tempCoords.find(std::get<1>(edge))->second.second));
    }

    /* Paint stadium (red or blue based on league) and print the name of the stadium */
    for(auto pair : tempCoords)
    {
        // Find stadium by id, get it's name and convert it to Qstring
        QString stadiumName(QString::fromStdString(Database::findStadiumById(pair.first).getName()));
        // For each coordinate paint the stadium
        paintStadiums(painter, pair.first,QPoint(pair.second.first,pair.second.second), stadiumName);
    }
}
