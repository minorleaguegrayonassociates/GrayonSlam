#pragma once
#include <string>
#include <array>

/**
 * @class Team class
 *
 * This class holds information about a team. It can be
 * hidden from public use by the @a hidden property.
 *
 * A team with an ID of -1 means it's invalid.
 *
 * Note:
 * All team IDs are defaulted to -1. The only way for a
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
    static const std::array<std::string,2> LEAGUE_STRING;

    /* Constructors */
    Team();

    /* Getters */
    int getId() const;
    std::string getName() const;

    /* Setters */
    void setName(const std::string&);

    /* Public data */
    bool hidden = true;
    League league = NATIONAL;

private:
    /* Constructors */
    Team(int id, const std::string& name, League);

    /* Data */
    int m_id = -1;
    std::string m_name = "invalid";
};
