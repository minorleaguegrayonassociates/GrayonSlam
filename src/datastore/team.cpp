#include "team.hpp"

/* Enum to strings */
const std::array<std::string,2> Team::LEAGUE_STRING = {"National", "American"};

/**
 * Constructs an invalid team.
 */
Team::Team()
{}

int Team::getId() const
{
    return m_id;
}

std::string Team::getName() const
{
    return m_name;
}

/**
 * Sets the team name only if the given string is not empty.
 *
 * @param name Team name
 */
void Team::setName(const std::string& name)
{
    if(!name.empty()) { m_name = name; }
}

/**
 * Private constructor used by @a Database through friend class
 * association. This sets all the data for the object besides
 * @a hidden; this is done so for better readability by forcing
 * it to be set on a different line and not buried in a
 * constructor's arguments.
 *
 * @param id Team ID
 * @param name Team name
 * @param leag Team's league
 */
Team::Team(int id, const std::string& name, League leag)
    : league(leag), m_id(id)
{
    setName(name);
}
