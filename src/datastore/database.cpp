#include "database.hpp"
#include "src/utils/parser.hpp"
#include "src/utils/enumtools.hpp"

/* Instantiate static map containers of teams and stadiums */
nstd::map<int,Team> Database::teams;
nstd::map<int,Stadium> Database::stadiums;

/**
 * @brief Loads team, stadium, and souvenir data
 *
 * This functions takes a path, extracts all the data and instantiates
 * team, stadium, and souvenir classes.
 *
 * @param filepath path to .csv data for teams,stadiums,and souvenirs
 */
void Database::loadFromFile(const std::string& filepath)
{
    /* all the variables that have "temp" temporarily hold data until the object is initialized and put into a container */
    // Temp Enum variables used to initialize class
    Team::League tempLeague;
    Stadium::Roof tempRoof;
    Stadium::Surface tempSurface;
    Stadium::Typology tempTypology;

    // Temp souvenir variables
    int souvenirCount;
    bool tempHidden;
    std::string tempName;
    double tempPrice;

    std::vector<std::vector<std::string>> teamData = loadData(filepath);
    for (const std::vector<std::string>& team : teamData)
    {
        // Converting all string values from strings to their enum values
        tempLeague = getEnumValue<Team::League>(Team::LEAGUE_STRING,team[8]);
        tempRoof = getEnumValue<Stadium::Roof>(Stadium::ROOF_STRING,team[12]);
        tempSurface = getEnumValue<Stadium::Surface>(Stadium::SURFACE_STRING,team[7]);
        tempTypology = getEnumValue<Stadium::Typology>(Stadium::TYPOLOGY_STRING,team[11]);

        // Initializing a new Team class
        Team tempTeam(std::stoi(team[0]), team[1], tempLeague);
        // Set's deleted bool
        tempTeam.hidden = std::stoi(team[2]);
        // Initializing a new Stadium class
        Stadium tempStadium(std::stoi(team[3]), std::stoi(team[0]), team[4], team[6], std::stoi(team[5]),std::stoi(team[9]),
                            std::stoi(team[10]), tempRoof, tempSurface, tempTypology);
        // Souvenir index starts at 14 for each team, reseting to 14 here
        // Used to traverser through souvenirs
        unsigned int j = 14;

        // Index 13 holds the number of souvenirs a stadium has
        souvenirCount = std::stoi(team[13]);
        for(int i = 0; i < souvenirCount; ++i)
        {
            tempHidden = std::stoi(team[j++]); // Is hidden? - bool
            tempName = team[j++];              // Souvenir Name
            tempPrice = std::stod(team[j++]);  // Souvenir Price

            tempStadium.addSouvenir(tempName, tempPrice); // Creating an instance of a souvenir class
            tempStadium.findSouvenir(i).hidden = tempHidden;
        }

        // Insterting team and stadium in to their appropriate maps for database
        teams[tempTeam.m_id] = tempTeam;
        stadiums[tempStadium.m_id] = tempStadium;
    }
}

/**
 * This method returns all the teams
 *
 * @return teams is returned by value
 */
nstd::map<int,Team> Database::getTeams()
{
    return teams;
}

/**
 * This method returns all the Stadiums
 *
 * @return stadiums is returned by value
 */
nstd::map<int,Stadium> Database::getStadiums()
{
    return stadiums;
}

/**
 * Finds team by it's id.
 *
 * @param id an int id used to find a Team
 * @return A const reference to a Team object
 */
Team& Database::findTeamById(int id)
{
    return teams[id];
}

/**
 * Finds Stadium by it's id.
 *
 * @param id an int id used to find a Stadium
 * @return A const reference to a Stadium object
 */
Stadium& Database::findStadiumById(int id)
{
    return stadiums[id];
}


/**
 * Returns a vector with all the Teams and stadiums
 *
 * @return A vector with all the teams and stadiums as a pair of team and stadium
 */
std::vector<std::pair<Team,Stadium>> Database::getTeamsAndStadiums()
{
    std::vector<std::pair<Team,Stadium>> vec;

    for(auto stadium : stadiums)
        vec.push_back(std::pair<Team,Stadium>(Database::findTeamById(stadium.getTeamId()),stadium));

    return vec;
}

/**
 * Uses the data within this class to write out the data
 * to a csv file.
 *
 * @param path Where the program will write the csv file.
 */
void Database::saveToFile(const std::string& path)
{
    /* Get all team and stadium data, create a temp vector that will be used to store souvenir data */
    std::vector<std::pair<Team,Stadium>> teamStadiumData(Database::getTeamsAndStadiums());


    // Initializing - vector will hold all lines of data within the document
    std::vector<std::vector<std::string>> allRows;

    /* Temp Enum variables used to hold string of enum */
    std::string tempLeague;
    std::string tempRoof;
    std::string tempSurface;
    std::string tempTypology;

    /* rowHeader hold the header of a save file */
    std::vector<std::string> rowHeader;
    rowHeader.push_back("# id, team name, hidden bool, id, stadium name, capacity, location, playing surface");
    rowHeader.push_back(" league, date opened, distance to center field, ballpark typology, Rooftype");
    allRows.push_back(rowHeader);

    for(unsigned int i = 0; i < teamStadiumData.size(); ++i)
    {
        // Will hold all the columns within a given row
        std::vector<std::string> columns;

        /* Convert enum values to their string enum version */
        tempLeague = Team::LEAGUE_STRING[teamStadiumData[i].first.league];
        tempRoof = Stadium::ROOF_STRING[teamStadiumData[i].second.roof];
        tempSurface = Stadium::SURFACE_STRING[teamStadiumData[i].second.surface];
        tempTypology = Stadium::TYPOLOGY_STRING[teamStadiumData[i].second.typology];

        /* Adds all the data that belongs to team and it's stadium to the columns vector */
        columns.push_back(std::to_string(teamStadiumData[i].first.getId()));
        columns.push_back(teamStadiumData[i].first.getName());
        columns.push_back(std::to_string(teamStadiumData[i].first.hidden));
        columns.push_back(std::to_string(teamStadiumData[i].second.getId()));
        columns.push_back(teamStadiumData[i].second.getName());
        columns.push_back(std::to_string(teamStadiumData[i].second.getSeatCap()));
        columns.push_back(teamStadiumData[i].second.getLocation());
        columns.push_back(tempSurface);
        columns.push_back(tempLeague);
        columns.push_back(std::to_string(teamStadiumData[i].second.getYearOpened()));
        columns.push_back(std::to_string(teamStadiumData[i].second.getCenterFieldDist()));
        columns.push_back(tempTypology);
        columns.push_back(tempRoof);

        // Get's a vector of the teams souvenirs
        std::vector<Souvenir> tempSouvenirVect = teamStadiumData[i].second.getSouvenirs();
        // Number of souvenirs
        columns.push_back(std::to_string(tempSouvenirVect.size()));

        for(const Souvenir& item: tempSouvenirVect)
        {
            /* add all the teams souvenir data to the columns vector */
            columns.push_back(std::to_string(item.hidden));
            columns.push_back(item.getName());
            std::string strPrice(std::to_string(item.getPrice()));
            // Erasing trailing zeros
            strPrice.erase( strPrice.find_first_of(".") + 3, std::string::npos);
            columns.push_back(strPrice);
        }
        /* Go though all the strings and check if it contains commas, add quotes if so */
        for(std::string& column:columns)
        {
            std::size_t found = column.find(",");
            if (found!=std::string::npos)
            {
                column = "\""+column+"\"";
            }
        }
        // All the columns in a row are input, push back columns
        allRows.push_back(columns);
    }
    // Call saveData to store data at the path provided
    saveData(path, allRows);
}
