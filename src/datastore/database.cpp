#include "database.hpp"
#include "./../utils/parser.hpp"

/**
 * Instantiate static map containers of teams and stadiums
 */
std::map<int,Team> Database::m_teams;
std::map<int,Stadium> Database::m_stadiums;

/**
 * Instantiate a static database object
 */
Database* Database::m_database = new Database();

/**
 * Constructor
 */
Database::Database()
{}

/**
 * Destructor
 */
Database::~Database()
{}


/**
 * @brief Loads team, stadium, and souvenir data
 *
 * This functions takes a path, extracts all the data and instantiates
 * team, stadium, and souvenir classes.
 *
 * @param filepath path to .csv data for teams,stadiums,and souvenirs
 * @return Nothing
 */
void Database::loadFromFile(const std::string& filepath)
{
    // Used to traverser through souvenirs
    unsigned int j;

    // Temp pointers that will hold initialized classes
    Stadium* tempStadium;
    Team* tempTeam;

    // Temp Enum variables used to initialize class
    Team::League tempLeague;
    Stadium::Roof tempRoof;
    Stadium::Surface tempSurface;
    Stadium::Typology tempTypology;

    // Temp souvenir variables
    bool tempHidden;
    std::string tempName;
    double tempPrice;

    std::vector<std::vector<std::string>> teamData = loadData(filepath);
    for (const std::vector<std::string>& team : teamData)
    {
        // Converting all string values from strings to their enum values
        tempLeague = m_database->getEnumValue(Team::LEAGUE_STRING,team[8], Team::League::AMERICAN);
        tempRoof = m_database->getEnumValue(Stadium::ROOF_STRING,team[12], Stadium::Roof::OPEN);
        tempSurface = m_database->getEnumValue(Stadium::SURFACE_STRING,team[7], Stadium::Surface::GRASS);
        tempTypology = m_database->getEnumValue(Stadium::TYPOLOGY_STRING,team[11], Stadium::Typology::MODERN);

        // Initializing a new Team class
        tempTeam = new Team(std::stoi(team[0]), std::stoi(team[3]), team[1], tempLeague);
        // Set's deleted bool
        tempTeam->hidden = std::stoi(team[2]);
        // Initializing a new Stadium class
        tempStadium = new Stadium(std::stoi(team[3]), team[4], team[6], std::stoi(team[5]),std::stoi(team[9]),
                                  std::stoi(team[10]), tempRoof, tempSurface, tempTypology);
        // Souvenir index starts at 14 for each team, reseting to 14 here
        j = 14;
        // Index 13 holds the number of souvenirs a stadium has
        for(int i = 0; i < std::stoi(team[13]); ++i)
        {
            tempHidden = ((std::stoi(team[j++]) == 0)?false:true); // Is hidden? - bool
            tempName = team[j++];               // Souvenir Name
            tempPrice = std::stod(team[j++]);   // Souvenir Price

            tempStadium->addSouvenir(tempName, tempPrice); // Creating an instance of a souvenir class
            tempStadium->findSouvenir(i).hidden = tempHidden;
        }

        // Insterting team and stadium in to their appropriate maps for database
        m_teams.insert(std::pair<int,Team>(tempTeam->m_id,*tempTeam));
        m_stadiums.insert(std::pair<int,Stadium>(tempStadium->m_id, *tempStadium));
    }
}

/**
 * @brief returns map of Teams
 *
 * This method returns all the stadiums that are
 * contianed within the database's map container.
 *
 * @param none
 * @return m_teams is returned
 */
std::map<int,Team> Database::getTeams()
{
    return m_teams;
}

/**
 * @brief returns map of Stadiums
 *
 * This method returns all the Stadiums that are
 * contianed within the database's map container.
 *
 * @param none
 * @return m_stadiums is returned
 */
std::map<int,Stadium> Database::getStadiums()
{
    return m_stadiums;
}

/**
 * Finds team by it's id.
 *
 * @param id an int id used to find a Team
 * @return A const reference to a Team object
 */
const Team& Database::findTeamById(int id)
{
    return m_teams[id];
}

/**
 * Finds Stadium by it's id.
 *
 * @param id an int id used to find a Stadium
 * @return A const reference to a Stadium object
 */
const Stadium& Database::findStadiumById(int id)
{
    return m_stadiums[id];
}


/**
 * Returns a vector with all the Teams
 *
 * @param none
 * @return A vector with all the teams within m_teams
 */
std::vector<Team> Database::getTeamsVector()
{
    std::vector<Team> vec;

    for(auto team : m_teams)
        vec.push_back(team.second);

    return vec;
}

/**
 * Returns a vector with all the Stadiums
 *
 * @param none
 * @return A vector with all the teams within m_stadiums
 */
std::vector<Stadium> Database::getStadiumsVector()
{
    std::vector<Stadium> vec;

    for(auto team : m_teams)
        vec.push_back(m_stadiums[team.second.getStadiumId()]);

    return vec;
}

/**
 * Uses the data within this class to write out the data
 * to a csv file.
 *
 * @param path Where the program will write the csv file.
 * @return nothing
 */
void Database::saveToFile(const std::string& path)
{
    std::vector<Team> tempTeamVector(Database::getTeamsVector());
    std::vector<Stadium> tempStadiumVector(Database::getStadiumsVector());
    saveData(path,tempTeamVector,tempStadiumVector);
}
