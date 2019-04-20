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
    /* Aliases */
    using completedEdge = std::vector<std::tuple<int,int,int>>;  //"from" <-> "to" and distance
    using coords = std::map<int,std::pair<int,int>>; // stadium Id, std::pair<int,int>(x-Coordinate,y-Coordinate)

    /* Static methods to Load and Save from/to file */
    static void loadFromFile(const std::string&);
    static void saveToFile(const std::string&);
    static void loadDistancesFromFile(const std::string&);

    /* Getters */
    static nstd::map<int,Team> getTeams();
    static nstd::map<int,Stadium> getStadiums();
    static Team& findTeamById(int);
    static Stadium& findStadiumById(int);
    static std::vector<std::pair<Team,Stadium>> getTeamsAndStadiums();
    static completedEdge getDistances();
    const static coords& getCoordinates();

private:
    /* Private static variables */
    static nstd::map<int,Team> teams;
    static nstd::map<int,Stadium> stadiums;
    static completedEdge distances;
    static coords coordinates;
};
