#pragma once

#include <vector>
#include "souvenir.hpp"
#include "stadium.hpp"
#include "team.hpp"

/**
 * @class Database class
 *
 * This class holds all of the programs data.
 * It contains a map of teams and a map of stadiums.
 * Each stadium has a vector of souvenirs within it's class.
 *
 * All the members aside from getEnumValue are static
 */
class Database
{
public:
    /* Constructor */
    Database();

    /* Destructor */
    ~Database();

    /* Static methods to Load and Save from/to file */
    static void loadFromFile(const std::string&);
    static void saveToFile(const std::string&);

     /* Getters */
    static std::map<int,Team> getTeams();
    static std::map<int,Stadium> getStadiums();
    static const Team& findTeamById(int);
    static const Stadium& findStadiumById(int);
    static std::vector<Team> getTeamsVector();
    static std::vector<Stadium> getStadiumsVector();

private:
    /* Private string to Enum method*/
    template<typename Container, typename Enum>
    Enum getEnumValue(Container , std::string , Enum);

    /* Private static variables */
    static Database* m_database;
    static std::map<int,Team> m_teams;
    static std::map<int,Stadium> m_stadiums;
};



/**
 * @brief Converts a string to it's enum type
 *
 * Takes in a string array, string, and the base enum
 * and goes through the string array until it finds a
 * string that matches the input string. The enum increments
 * after each iteration and will return at the same index as
 * where the string was found within the string array
 *
 * @param Arr array of strings. Enum version of the strings
 * @param strVal string version of the enum that will be converted
 * @param enumVal base enum of the string that's being converted
 */
template<typename Container, typename Enum>
Enum Database::getEnumValue(Container arr, std::string strVal, Enum enumVal)
{
    // Arrays are automatically passed by reference
    enumVal = static_cast<Enum>(0);
    /* Iterating through the string array until it finds a match with strVal */
    for(auto it = arr.begin(); it != arr.end(); ++it)
    {
        /* If it matches return the enumVal, otherwise incement it by 1 */
        if(*it == strVal)
            return enumVal;
        else
            enumVal = static_cast<Enum>(enumVal+1);
    }
    // Won't reach this as long as datafile isn't changed manually -- added to prevent warnings from Qt
    return enumVal;
}
