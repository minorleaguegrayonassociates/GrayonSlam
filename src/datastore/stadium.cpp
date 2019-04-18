#include "stadium.hpp"

/* Enum to strings */
const std::array<std::string,3> Stadium::ROOF_STRING = {"Retractable", "Open", "Fixed"};
const std::array<std::string,2> Stadium::SURFACE_STRING = {"Grass", "AstroTurf GameDay Grass"};
const std::array<std::string,6> Stadium::TYPOLOGY_STRING = {"Retro Modern", "Retro Classic", "Jewel Box",
                                                            "Modern", "Contemporary", "Multipurpose"};

/**
 * Constructs an invalid stadium.
 */
Stadium::Stadium()
{}

int Stadium::getId() const
{
    return m_id;
}

int Stadium::getTeamId() const
{
    return m_teamId;
}

std::string Stadium::getName() const
{
    return m_name;
}

std::string Stadium::getLocation() const
{
    return m_location;
}

int Stadium::getSeatCap() const
{
    return m_seatCap;
}

int Stadium::getYearOpened() const
{
    return m_yearOpened;
}

int Stadium::getCenterFieldDist() const
{
    return m_centerFieldDist;
}

std::vector<Souvenir> Stadium::getSouvenirs() const
{
    std::vector<Souvenir> vec;

    for(auto souvenir : m_souvenirs)
        vec.push_back(souvenir.second);

    return vec;
}

/**
 * Sets the stadium's team ID reference to the argument's ID.
 *
 * @param team Team that resides in the stadium
 */
void Stadium::setTeam(const Team& team)
{
    m_teamId = team.getId();
}

/**
 * Sets the stadium name only if the given string is not empty.
 *
 * @param name Stadium name
 */
void Stadium::setName(const std::string& name)
{
    if(!name.empty()) { m_name = name; }
}

/**
 * Sets the stadium location only if the given string is not empty.
 *
 * @param location Stadium location
 */
void Stadium::setLocation(const std::string& location)
{
    if(!location.empty()) { m_location = location; }
}

/**
 * Sets the stadium's seating capacity only if the given capacity
 * is non-negative.
 *
 * @param cap Stadium's seating capacity
 */
void Stadium::setSeatCap(int cap)
{
    if(cap >= 0) { m_seatCap = cap; }
}

/**
 * Sets the stadium's opening year only if the given year is
 * greater than or equal 1800.
 *
 * @param year Stadium's opening year
 */
void Stadium::setYearOpened(int year)
{
    if(year >= 1839) { m_yearOpened = year; }
}

/**
 * Sets the stadium's distance to the center field only if the
 * given distance is non-negative.
 *
 * @param dist Stadium's distance to the center field
 */
void Stadium::setCenterFieldDist(int dist)
{
    if(dist >= 0) { m_centerFieldDist = dist; }
}

/**
 * @brief Add a new souvenir
 *
 * Creates a new souvenir with the given name and price. The
 * souvenir's ID is set by keeping track of how many the
 * stadium currently has. It is then added to map.
 *
 * @param name Souvenir name to add
 * @param price Souvenir price to add
 */
void Stadium::addSouvenir(const std::string& name, double price)
{
    Souvenir souvenir(m_nextSouvenirId, name, price);
    m_souvenirs[m_nextSouvenirId] = souvenir;
    m_nextSouvenirId++;
}

/**
 * Finds a souvenir given a souvenir ID.
 *
 * @param id ID of souvenir to find
 * @return If found, returns the souvenir.
 *         If not found, returns an invalid souvenir.
 */
Souvenir& Stadium::findSouvenir(int id)
{
    return m_souvenirs[id];
}

/**
 * Private constructor used by @a Database through friend class
 * association. This sets all the data for the object besides
 * @a hidden; this is done so for better readability by forcing
 * it to be set on a different line and not buried in a
 * constructor's arguments.
 *
 * @param id Stadium ID
 * @param teamId ID of the team that resides in this stadium
 * @param name Stadium name
 * @param location Stadium location
 * @param seatCap Stadium's seat capacity
 * @param yearOpened Stadium's opening year
 * @param centerFieldDist Stadium's distance to the center field
 * @param r Stadium's roof
 * @param s Stadium's playing surface
 * @param t Stadium's typology
 */
Stadium::Stadium(int id, int teamId,
                 const std::string& name, const std::string& location,
                 int seatCap, int yearOpened, int centerFieldDist,
                 Roof r, Surface s, Typology t)
    : roof(r), surface(s), typology(t), m_id(id), m_teamId(teamId)
{
    setName(name);
    setLocation(location);
    setSeatCap(seatCap);
    setYearOpened(yearOpened);
    setCenterFieldDist(centerFieldDist);
}
