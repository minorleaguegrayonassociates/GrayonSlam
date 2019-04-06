#pragma once

#include "souvenir.hpp"
#include "stadium.hpp"
#include "team.hpp"

/**
 * @class Database class
 *
 * This class holds all of the programs data. It contains instances of the team
 * class and instances of the stadium class which holds a map container
 * populated with instances the Souvenier class.
 */
class Database
{
public:
    /* Public static variables */
    static void loadFromFile(const std::string&);
    static void saveToFile(const std::string&);

    static std::map<int,Team> getTeams();
    static std::map<int,Stadium> getStadiums();

    static const Team& findTeamById(int);
    static const Stadium& findStadiumById(int);

    template<typename Container, typename Enum>
    Enum getEnumValue(Container , std::string , Enum);

    Database();
    ~Database();
private:
    /* Private static variables */
    static Database* m_database;
    static std::map<int,Team> m_teams;
    static std::map<int,Stadium> m_stadiums;
};

template<typename Container, typename Enum>
Enum Database::getEnumValue(Container arr, std::string strVal, Enum enumVal)
{
    for(auto it = arr.begin(); it != arr.end(); ++it)
    {
        if(*it == strVal)
            return enumVal;
        else
            enumVal = static_cast<Enum>(enumVal+1);
    }
    // Won't reach this as long as datafile isn't changed manually -- added to prevent warnings from Qt
    return enumVal;
}
