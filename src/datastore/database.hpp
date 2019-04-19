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
    static std::vector<std::pair<Team,Stadium>> getTeamsAndStadiums();

private:
    /* Private Constructor */
    Database();

    /* Private static variables */
    static Database* database;
    static nstd::map<int,Team> teams;
    static nstd::map<int,Stadium> stadiums;
};
