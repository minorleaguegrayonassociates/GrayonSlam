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
 *
 * Note:
 * All teams have their IDs defaulted to -1. The only way for a
 * team to have a valid ID is for it to be created by the
 * @a Database class. This is why @a Database is a friend class.
 */
class Team
{
public:
    friend class Database;

    /* Enum types */
    enum League { NATIONAL, AMERICAN };

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
    /* Constructors */
    Team(int id, int stadiumId, const std::string& name, League);

    /* Data */
    int m_id = -1;
    int m_stadiumId = -1;
    std::string m_name = "invalid";
};
