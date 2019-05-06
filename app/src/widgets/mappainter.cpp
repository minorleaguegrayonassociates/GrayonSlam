#include "mappainter.hpp"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "airplanerotationanimation.hpp"
#include <cmath>

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
    m_airplane->setHidden(true);

    /* Making an instance of Beacon - signals `To` location when animating */
    m_beacon = new Beacon(this);

    /* Making an instance of Beacon that show's if the coordinates are set publicly */
    m_publicBeacon = new Beacon(this);
}

/* Destuctor */
MapPainter::~MapPainter()
{
    delete m_airplane;
    delete m_beacon;
}

/**
 * Finds the coodinates (x,y) of the stadium id passed in and creates a QPoint
 * that is assigned to `m_coords`, set's `m_publicBeacon` to `m_coords`
 *
 * @param stadiumId stadium id
 */
void MapPainter::setBeaconCoords(int stadiumId)
{
    // Get map of stadium coordinates
    std::map<int,Database::coords> coords(Database::getCoordinates());

    // find Stadium id x,y coordinates and set `m_coords`
    m_coords = QPoint(coords.find(stadiumId)->second.first,coords.find(stadiumId)->second.second);
    m_publicBeacon->setCoords(m_coords);
    m_publicBeacon->update();
}

/**
 * Set's distcoveredEdges list so that the
 * painter can highlight the discovered path
 * alternate container to `m_discoveredEdgesVector`
 *
 * @param discoveredEdges list of completed edges
 */
void MapPainter::setDiscoveredEdges(const std::list<Database::completedEdge>& discoveredEdges)
{
    /* If alternate list is empty then set vector */
    if(m_discoveredEdgesVector.empty())
        m_discoveredEdgesList = discoveredEdges;
}

/**
 * Set's distcoveredEdges vector so that the
 * painter can highlight the discovered path
 * alternate container to `m_discoveredEdgesList`
 *
 * @param discoveredEdges vector std::pair<std::list<std::pair<int,int>>,int> list constains edge(s)
 */
void MapPainter::setDiscoveredEdges(const std::vector<std::pair<std::list<std::pair<int,int>>,int>>& discoveredEdges)
{
    /* If alternate list is empty then set vector */
    if(m_discoveredEdgesList.empty())
        m_discoveredEdgesVector = discoveredEdges;
}

/**
 * @brief set's airplane and beacon so that they're out of site of the MapView when a user enter's the view
 */
void MapPainter::resetMap()
{
    // Set to hidden
    m_airplane->setHidden(true);

    /* Set beacon coordinates outside of widget coordinates */
    m_beacon->setCoords(Beacon::outerBound);
    m_coords = Beacon::outerBound;
    m_publicBeacon->setCoords(Beacon::outerBound);

    if(!m_discoveredEdgesVector.empty())
        m_discoveredEdgesVector.clear();

    if(!m_discoveredEdgesList.empty())
        m_discoveredEdgesList.clear();
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
void MapPainter::highlightDiscoveredEdges(QPainter& painter, std::list<Database::completedEdge>& discoveredEdges)
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
 * highlights lines between the container of edges provided
 * made to highlight a trips discovered edges
 *
 * @param painter QPainter
 * @param discoveredEdges vector of std::pair<std::list<std::pair<int,int>>,int>
 */
void MapPainter::highlightDiscoveredEdges(QPainter& painter, std::vector<std::pair<std::list<std::pair<int,int>>,int>>& discoveredEdges)
{
    std::map<int,Database::coords> coords(Database::getCoordinates());
    for(auto edges: discoveredEdges)
        for(auto edge : edges.first)
        highlightEdge(painter, QPoint(coords.find(edge.first)->second.first,
                                      coords.find(edge.first)->second.second),
                          QPoint(coords.find(edge.second)->second.first,
                                 coords.find(edge.second)->second.second));
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

/*
 * Animates a whole trip, meant to simulate a whole trip
 * as a preview
 *
 * @param tripEdges std::vector<std::pair<std::list<std::pair<int,int>>,int>>
*/
void MapPainter::animateTrip(std::vector<std::pair<std::list<std::pair<int,int>>,int>>& tripEdges)
{
    /* As long as you're not on the very last list in the vector always go through all the last edge of a list
     * and check if the last distination is different from the start of the next destination on the next set of
     * edges if so then trace back and pop in the inverse of the original edge until you get to the vertex where
     * the route diviated
     */
    size_t tripSize = tripEdges.size();
    for(size_t i = 0; i < tripSize; ++i)
    {
        if(i != tripSize-1)
        {
        /* While the last destination of a list isn't equal to the start of the next destination on the next list
             * it will trace back and pop the inverese edge and check if
             */
        while(tripEdges[i].first.back().second != tripEdges[i+1].first.front().first)
        {
            std::list<std::pair<int,int>>::const_iterator it = tripEdges[i].first.end();
            if( it == tripEdges[i].first.end())
                --it;
            if(it->second != tripEdges[i+1].first.front().first)
            {
                tripEdges[i].first.push_back(std::pair<int,int>(it->second,it->first));
            }
            else
            {
                break;
            }
        }
        }

        QSequentialAnimationGroup* group = new QSequentialAnimationGroup;

        // Always set airplane visable before use
        m_airplane->setHidden(false);

        // Getting the coordinates of all the stadiums
        std::map<int,Database::coords> tempCoords(Database::getCoordinates());

        double prevEndAngle = 0;
        double endAngle = 0;
        for(auto trips : tripEdges)
        {
            for(auto trip : trips.first)
            {
                /* Set up for plane rotation */
                prevEndAngle = endAngle;
                endAngle = atan2(tempCoords[trip.second].second-tempCoords[trip.first].second,tempCoords[trip.second].first-tempCoords[trip.first].first)*(180.0/M_PI);
                AirplaneRotationAnimation* rotation = new AirplaneRotationAnimation(m_airplane);
                rotation->setEasingCurve(QEasingCurve::OutExpo);
                rotation->setDuration(50);
                rotation->setStartValue(QVariant(prevEndAngle));
                rotation->setEndValue(QVariant(endAngle));
                group->addAnimation(rotation);

                /* setting up m_airplane to animate between two stadium coordinates */
                QPropertyAnimation* animation = new QPropertyAnimation(m_airplane, "geometry");
                animation->setDuration(600);
                animation->setStartValue(QRect(QPoint(tempCoords[trip.first].first-m_airplane->size().width()/2,
                                                      tempCoords[trip.first].second-m_airplane->size().height()/2),
                                               m_airplane->size()));
                animation->setEndValue(QRect(QPoint(tempCoords[trip.second].first-m_airplane->size().width()/2,
                                                    tempCoords[trip.second].second-m_airplane->size().height()/2),
                                             m_airplane->size()));
                group->addAnimation(animation);
            }
        }

        // Set beacon last stadium location in the preview
        m_beacon->setCoords(QPoint(tempCoords[tripEdges.back().first.back().second].first,tempCoords[tripEdges.back().first.back().second].second));

        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

/*
 * Animates a set of edges
 *
 * @param tripEdges std::list<Database::completedEdge>
*/
void MapPainter::animateTrip(const std::pair<std::list<std::pair<int,int>>,int>& tripEdges)
{
    QSequentialAnimationGroup* group = new QSequentialAnimationGroup;
    // Always set airplane visable before use
    m_airplane->setHidden(false);

    // Getting the coordinates of all the stadiums
    std::map<int,Database::coords> tempCoords(Database::getCoordinates());

    double prevEndAngle = 0;
    double endAngle = 0;
    for(auto trip : tripEdges.first)
    {
        /* Set up for plane rotation */
        prevEndAngle = endAngle;
        endAngle = atan2(tempCoords[trip.second].second-tempCoords[trip.first].second,tempCoords[trip.second].first-tempCoords[trip.first].first)*(180.0/M_PI);
        AirplaneRotationAnimation* rotation = new AirplaneRotationAnimation(m_airplane);
        rotation->setEasingCurve(QEasingCurve::OutExpo);
        rotation->setDuration(50);
        rotation->setStartValue(QVariant(prevEndAngle));
        rotation->setEndValue(QVariant(endAngle));
        group->addAnimation(rotation);

        /* setting up m_airplane to animate between two stadium coordinates */
        QPropertyAnimation* animation = new QPropertyAnimation(m_airplane, "geometry");
        animation->setDuration(600);
        animation->setStartValue(QRect(QPoint(tempCoords[trip.first].first-m_airplane->size().width()/2,
                                              tempCoords[trip.first].second-m_airplane->size().height()/2),
                                       m_airplane->size()));
         animation->setEndValue(QRect(QPoint(tempCoords[trip.second].first-m_airplane->size().width()/2,
                                            tempCoords[trip.second].second-m_airplane->size().height()/2),
                                     m_airplane->size()));
         group->addAnimation(animation);
    }

    // Set beacon last stadium location in the preview
    m_beacon->setCoords(QPoint(tempCoords[tripEdges.first.back().second].first,tempCoords[tripEdges.first.back().second].second));

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

/**
 * @brief Draws all stadiums and all the edges between the stadiums
 */
void MapPainter::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    std::map<int,Database::coords> tempCoords(Database::getCoordinates());

    /* If m_discoverEdgesList is populated with edges, highlight discovered edges */
    if(!m_discoveredEdgesList.empty())
    {
        highlightDiscoveredEdges(painter, m_discoveredEdgesList);
    }

    /* If m_discoverEdgesVector is populated with edges, highlight discovered edges */
    if(!m_discoveredEdgesVector.empty())
    {
        highlightDiscoveredEdges(painter, m_discoveredEdgesVector);
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
