#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "../src/datastore/team.hpp"

std::string randomString(int length)
{
    std::string string;

    for(int i = 0; i < length; i++)
        string += rand() % ('Z' - 'A') + 'A';

    return string;
}

int main()
{
    std::vector<Team> teams;

    /* Create teams and put them into the vector */
    for(int i = 0; i < 10; i++)
    {
        Team team(randomString(5), Team::League::NATIONAL);
        team.hidden = false;

        //Assign every other team to american league
        if(i % 2 == 0)
        {
            team.league = Team::League::AMERICAN;
        }

        teams.push_back(team);
    }

    /* Display each team's info */
    for(Team team : teams)
    {
        std::cout << std::setw(12) << "ID: "         << team.getId()        << std::endl
                  << std::setw(12) << "Stadium ID: " << team.getStadiumId() << std::endl
                  << std::setw(12) << "Name: "       << team.getName()      << std::endl
                  << std::setw(12) << "League: "     << Team::LEAGUE_STRING[team.league]
                  << std::endl << std::endl;
    }
    
    return 0;
}
