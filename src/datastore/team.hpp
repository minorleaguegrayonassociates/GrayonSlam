#pragma once
#include <string>

/**
 * @class Team class
 *
 * This class holds information about a team. It can be
 * hidden from public use by the @a hidden property. Other
 * properties of the team can be changed through @a getter
 * functions.
 */
class Team
{
public:
    enum class League { NATIONAL, AMERICAN };

    /* Constructors */
    Team(const std::string& name, League);

    /* Getters */
    int getId() const;
    int getStadiumId() const;
    std::string getName() const;

    /* Setters */
    void setName(const std::string&);
    void setStadiumId(int);

    /* Public data */
    bool hidden = true;
    League league = League::NATIONAL;

private:
    /* Static variables */
    static int nextId;

    /* Data */
    int m_id = -1;
    int m_stadiumId = -1;
    std::string m_name;
};
