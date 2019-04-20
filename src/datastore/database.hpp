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
    using completedEdge = std::tuple<int,int,int>;  //"from" <-> "to" and distance
    using coords = std::pair<int,int>; // std::pair<int,int>(x-Coordinate,y-Coordinate)

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
    const static std::map<int,completedEdge>& getDistances();
    const static std::map<int,coords>& getCoordinates();

private:
    /* Private static variables */
    static nstd::map<int,Team> teams;
    static nstd::map<int,Stadium> stadiums;
    static std::map<int,completedEdge> distances;
    static std::map<int,coords> coordinates;
};
