#include "database.hpp"
#include "./../utils/parser.hpp"

std::map<int,Team> Database::m_teams;
std::map<int,Stadium> Database::m_stadiums;

Database* Database::m_database = new Database();

Database::Database()
{}

Database::~Database()
{}


/* loadFromFile
 *
 * @param filepath path to csv data file
 *
 * ----------Team ID:  0"
 *---------Team Name:  1"
 *----------Deleted?:  2"
 *--------Stadium ID:  3"
 *------Stadium Name:  4"
 *--Seating Capacity:  5"
 *-----Team Location:  6"
 *---Playing Surface:  7"
 *------------League:  8"
 *-------Date opened:  9"
 *---Distance2CtrFld: 10"
 *-Ballpark typology: 11"
 *---------Roof Type: 12"
 *--NumberOSouvenirs: 13"*/

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
    bool tempDeleted;
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
            tempDeleted = (team[j++] == "0") ? true:false; // Is deleted? - bool
            tempName = team[j++];               // Souvenir Name
            tempPrice = std::stod(team[j++]);   // Souvenir Price

            tempStadium->addSouvenir(tempName, tempPrice); // Creating an instance of a souvenir class
            tempStadium->getSouvenirs()[static_cast<unsigned int>(i)].hidden = tempDeleted;
        }

        // Insterting team and stadium in to their appropriate maps for database
        m_teams.insert(std::pair<int,Team>(tempTeam->m_id,*tempTeam));
        m_stadiums.insert(std::pair<int,Stadium>(tempStadium->m_id, *tempStadium));
    }
}

void Database::saveToFile(const std::string&)
{

}

std::map<int,Team> Database::getTeams()
{
    return m_teams;
}

std::map<int,Stadium> Database::getStadiums()
{
    return m_stadiums;
}

const Team& Database::findTeamById(int id)
{
    return m_teams[id];
}

// Find stadium by id
const Stadium& Database::findStadiumById(int id)
{
    return m_stadiums[id];
}

// Goes though Each team and push_back the teams onto a list
std::vector<Team> Database::getTeamsVector()
{
    std::vector<Team> vec;

    for(auto team : m_teams)
        vec.push_back(team.second);

    return vec;
}

// Goes though Each team and push_back the teams' stadium onto a list
std::vector<Stadium> Database::getStadiumsVector()
{
    std::vector<Stadium> vec;

    for(auto team : m_teams)
        vec.push_back(m_stadiums[team.second.getStadiumId()]);

    return vec;
}

