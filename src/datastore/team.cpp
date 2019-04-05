#include "team.hpp"

/* Enum to strings */
const std::array<std::string,2> LEAGUE_STRING = {"National", "American"};

/**
 * Constructs an invalid team.
 */
Team::Team()
{}

/**
 * Constructs a team given a name and league. ID data will be
 * defaulted to -1. Enum data is set to the first item in the enum.
 *
 * If @a name is an empty string, the team's name is set to "invalid".
 *
 * The stadium ID is set to -1 to indicate that the team is not
 * in a stadium yet.
 *
 * @param name Team name
 * @param leag Team's league
 */
Team::Team(const std::string& name, League leag)
    : league(leag)
{
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

/**
 * Private constructor used by @a Database through friend class
 * association. This sets the id, name, and league of the team.
 *
 * @param id Team ID
 * @param name Team name
 * @param leag Team's league
 */
Team::Team(int id, const std::string& name, League leag)
    : Team(name, leag)
{
    m_id = id;
}
