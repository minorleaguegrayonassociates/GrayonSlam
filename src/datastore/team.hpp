#pragma once
#include "stadium.hpp"

/**
 * @class Team class
 *
 * This class holds information about a team. It can be
 * hidden from public use by the @a hidden property.
 *
 * A team with an ID of -1 means it's invalid.
 *
 * A team with a stadium ID of -1 means it doesn't reside
 * in a stadium.
 */
class Team
{
public:
    friend class DataStore;

    /* Enum types */
    enum class League { NATIONAL, AMERICAN };

    /* Enum to strings */
    static const std::string LEAGUE_STRING[];

    /* Constructors */
    Team();
    Team(const std::string& name, League);

    /* Getters */
    int getId() const;
    int getStadiumId() const;
    std::string getName() const;

    /* Setters */
    void setStadium(const Stadium&);
    void setName(const std::string&);

    /* Public data */
    bool hidden = true;
    League league;

private:
    /* Static variables */
    static int nextId;

    /* Data */
    int m_id = -1;
    int m_stadiumId = -1;
    std::string m_name = "invalid";
};
