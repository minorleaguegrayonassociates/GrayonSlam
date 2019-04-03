#include "team.hpp"

/* Static variables */
int Team::nextId = 0;

/**
 * Constructs an invalid team.
 */
Team::Team()
{}

/**
 * Constructs a team given a name and league. The ID of this team
 * will be set to @a nextId, then @a nextId is incremented after.
 * If @a name is an empty string, the team's name is set to "invalid".
 *
 * The stadium ID is set to -1 to indicate that the team is not
 * in a stadium yet.
 *
 * @param name Team name
 * @param leag Team's league
 */
Team::Team(const std::string& name, League leag)
    : league(leag), m_id(nextId)
{
    nextId++;

    setName(name);
}

int Team::getId() const
{
    return m_id;
}

int Team::getStadiumId() const
{
    return m_stadiumId;
}

std::string Team::getName() const
{
    return m_name;
}

/**
 * Sets the stadium ID given a stadium object.
 *
 * @param stadium Team's stadium
 */
void Team::setStadium(const Stadium& stadium)
{
    m_stadiumId = stadium.getId();
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
