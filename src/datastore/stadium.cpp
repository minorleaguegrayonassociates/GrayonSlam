#include "stadium.hpp"
#include <stdexcept>

/* Enum to strings */
static const std::string ROOF_STRING[] = {"Rectractable", "Open", "Fixed"};
static const std::string SURFACE_STRING[] = {"Grass", "AstroTurg GameDay Grass",
                                             "AstroTurf GameDay Grass 3D"};
static const std::string TYPOLOGY_STRING[] = {"Retro Modern", "Retro Classic", "Jewelbox",
                                              "Modern", "Contemporary", "Multipurpose"};

/* Static variables */
int Stadium::nextId = 0;

/**
 * Constructs an invalid stadium.
 */
Stadium::Stadium()
{}

/**
 * Constructs a stadium given a name and location. The ID of this
 * stadium will be set to @a nextId, then @a nextID is incremented
 * after. The rest of the data is initialized to -1 (for integers)
 * or the first item in the enum.
 *
 * If @a name is an empty string, the name is set to "invalid".
 * If @a location is an empty string, the location is set to "invalid".
 *
 * @param name Stadium name
 * @param location Stadium location
 */
Stadium::Stadium(const std::string& name, const std::string& location)
    : m_id(nextId)
{
    nextId++;

    setName(name);
    setLocation(location);

    /*
     * Used when findSouvenir doesn't find a corresponding
     * souvenir with the searching ID. The function will
     * return the value at key -1, which is an uninitialized
     * souvenir.
     */
    m_souvenirs[-1] = Souvenir();
}

int Stadium::getId() const
{
    return m_id;
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
    if(year >= 1800) { m_yearOpened = year; }
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
    /*
     * Since Souvenir makes Stadium a friend class,
     * we can directly set the souvenir ID
     */
    Souvenir souvenir(name, price);
    souvenir.m_id = m_nextSouvenirId;

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
    auto iterator = m_souvenirs.find(id);
    return (iterator != m_souvenirs.end() ? (*iterator).second
                                          : m_souvenirs[-1]);
}
