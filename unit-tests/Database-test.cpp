#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "./../src/datastore/database.hpp"



int main()
{
	//Load - Initial database file. Path of MLBInformation.csv.
    Database::loadFromFile("./../../../src/datastore/MLBInformation.csv");
	//Load - Expansion database file.
    Database::loadFromFile("./../../../src/datastore/MLBInformationExpansion.csv");
	//Load - Original file again. Making sure there aren't any duplicates. Path of MLBInformation.csv.
    Database::loadFromFile("./../../../src/datastore/MLBInformation.csv");
    
	//Variable to hold team id
	int tempId;

	/* Temp containers */
	std::vector<Souvenir> tempSouvenir;
    std::map<int,Team> tempTeam(Database::getTeams());
    std::map<int,Stadium> tempStadium(Database::getStadiums());
    
	/* Display all the classes data */
	for(std::map<int,Team>::iterator it = tempTeam.begin(); it != tempTeam.end(); ++it)
    {
		tempId = it->second.getId();

        std::cout << "----------Team ID: " << tempId << std::endl;
        std::cout << "--------Team Name: " << it->second.getName() << std::endl;
        std::cout << "---------Deleted?: " << it->second.hidden << std::endl;
        std::cout << "-------Stadium ID: " << it->second.getStadiumId() << std::endl;
        std::cout << "-----Stadium Name: " << Database::findStadiumById(tempId).getName() << std::endl;
        std::cout << "-Seating Capacity: " << Database::findStadiumById(tempId).getSeatCap() << std::endl;
        std::cout << "----Team Location: " << Database::findStadiumById(tempId).getLocation() << std::endl;
        std::cout << "--Playing Surface: " << Database::findStadiumById(tempId).surface << std::endl;
        std::cout << "-----------League: " << it->second.league << std::endl;
        std::cout << "------Date opened: " << Database::findStadiumById(tempId).getYearOpened() << std::endl;
        std::cout << "--Distance2CtrFld: " << Database::findStadiumById(tempId).getCenterFieldDist() << std::endl;
        std::cout << "Ballpark typology: " << Database::findStadiumById(tempId).typology << std::endl;
        std::cout << "--------Roof Type: " << Database::findStadiumById(tempId).roof << std::endl;
		
        tempSouvenir = Database::findStadiumById(it->second.getStadiumId()).getSouvenirs();
        std::cout << "Num. of souvenirs: "<< tempSouvenir.size() << std::endl;

        for(const Souvenir& item: tempSouvenir)
        {
            std::cout << "---------ID   " << item.getId() << std::endl;
            std::cout << "Is deleted?:  " << item.hidden << std::endl;
            std::cout << "---Souvenir:  " << item.getName() << std::endl;
            std::cout << "------Price:  " << item.getPrice()<< std::endl;
        }
    } 
    return 0;
}
