#include "stadium.hpp"

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
 * @param name Stadium name
 * @param location Stadium location
 */
Stadium::Stadium(const std::string& name, const std::string& location)
    : m_id(nextId), m_name(name), m_location(location)
{
    nextId++;
}

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

/**
 * Sets the team ID only if the given ID is non-negative.
 *
 * @param id Team ID
 */
void Stadium::setTeamId(int id)
{
    if(id >= 0) { m_teamId = id; }
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
