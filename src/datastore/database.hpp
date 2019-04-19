#pragma once

#include <vector>
#include "src/datastore/souvenir.hpp"
#include "src/datastore/stadium.hpp"
#include "src/datastore/team.hpp"
#include "src/utils/map.hpp"

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
    /* Static methods to Load and Save from/to file */
    static void loadFromFile(const std::string&);
    static void saveToFile(const std::string&);

    /* Getters */
    const static nstd::map<int,Team> getTeams();
    const static nstd::map<int,Stadium> getStadiums();
    static Team& findTeamById(int);
    static Stadium& findStadiumById(int);
    static std::vector<Team> getTeamsVector();
    static std::vector<Stadium> getStadiumsVector();

private:
    /* Private Constructor */
    Database();

    /* Private static variables */
    static Database* database;
    static nstd::map<int,Team> teams;
    static nstd::map<int,Stadium> stadiums;
};

/**
 * @file database.hpp
 * @brief Converts a string to it's enum type
 *
 * Takes in a string array, string, and the base enum
 * and goes through the string array until it finds a
 * string that matches the input string. The enum increments
 * after each iteration and will return at the same index as
 * where the string was found within the string array
 *
 * @param container array of strings. Enum version of the strings
 * @param strVal string version of the enum that will be converted
 * @param enumVal base enum of the string that's being converted
 */
template<typename Container, typename Enum>
Enum getEnumValue(const Container& container,const std::string& strEnum, Enum enumVal)
{
    // Make sure enum is set to the base enum
    enumVal = static_cast<Enum>(0);
    /* Iterating through the string array until it finds a match with strEnum */
    for(auto it = container.begin(); it != container.end(); ++it)
    {
        /* If strEnum matches an index within the string array, return the enumVal at current index, otherwise incement it by 1 */
        if(*it == strEnum)
            return enumVal;
        else
            enumVal = static_cast<Enum>(enumVal+1);
    }
    // If it returns this value strEnums didn't convert properly to enumVal
    return enumVal;
}
