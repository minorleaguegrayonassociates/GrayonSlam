#include <QtTest>
#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "./../../GrayonSlam/src/datastore/database.hpp"
// add necessary includes here

class Init_classes : public QObject
{
Q_OBJECT

public:
Init_classes();
~Init_classes();

private slots:
void initTestCase();
void cleanupTestCase();
void test_case1();

};

Init_classes::Init_classes()
{
    Database::loadFromFile("./../../../src/MLBInformation.csv");
    Database::loadFromFile("./../../../src/MLBInformationExpansion.csv");
    Database::loadFromFile("./../../../src/MLBInformation.csv");
    std::vector<Souvenir> tempSouvenir;
    std::map<int,Team> tempTeam(Database::getTeams());
    std::map<int,Stadium> tempStadium(Database::getStadiums());
    for(std::map<int,Team>::iterator it = tempTeam.begin(); it != tempTeam.end(); ++it)
    {
        std::cout << "----------Team ID: " << it->second.getId() << std::endl;
        std::cout << "--------Team Name: " << it->second.getName() << std::endl;
        std::cout << "---------Deleted?: " << it->second.hidden << std::endl;
        std::cout << "-------Stadium ID: " << it->second.getStadiumId() << std::endl;
        std::cout << "-----Stadium Name: " << tempStadium[it->second.getStadiumId()].getName() << std::endl;
        std::cout << "-Seating Capacity: " << tempStadium[it->second.getStadiumId()].getSeatCap() << std::endl;
        std::cout << "----Team Location: " << tempStadium[it->second.getStadiumId()].getLocation() << std::endl;
        std::cout << "--Playing Surface: " << tempStadium[it->second.getStadiumId()].surface << std::endl;
        std::cout << "-----------League: " << it->second.league << std::endl;
        std::cout << "------Date opened: " << tempStadium[it->second.getStadiumId()].getYearOpened() << std::endl;
        std::cout << "--Distance2CtrFld: " << tempStadium[it->second.getStadiumId()].getCenterFieldDist() << std::endl;
        std::cout << "Ballpark typology: " << tempStadium[it->second.getStadiumId()].typology << std::endl;
        std::cout << "--------Roof Type: " << tempStadium[it->second.getStadiumId()].roof << std::endl;

        tempSouvenir = tempStadium[it->second.getStadiumId()].getSouvenirs();

        std::cout << "Num. of souvenirs: "<< tempSouvenir.size() << std::endl;

        for(const Souvenir& item: tempSouvenir)
        {
            std::cout << "---------ID   " << item.getId() << std::endl;
            std::cout << "Is deleted?:  " << item.hidden << std::endl;
            std::cout << "---Souvenir:  " << item.getName() << std::endl;
            std::cout << "------Price:  " << item.getPrice()<< std::endl;
        }
    }
    std::vector<Souvenir> tempSouvenirVect;
    std::vector<Team> tempTeamVector(Database::getTeamsVector());
    std::vector<Stadium> tempStadiumVector(Database::getStadiumsVector());
    for(unsigned int i = 0; i < tempTeamVector.size(); ++i)
    {
        std::cout << "----------Team ID: " << tempTeamVector[i].getId() << std::endl;
        std::cout << "--------Team Name: " << tempTeamVector[i].getName() << std::endl;
        std::cout << "---------Deleted?: " << tempTeamVector[i].hidden << std::endl;
        std::cout << "-------Stadium ID: " << tempTeamVector[i].getStadiumId() << std::endl;
        std::cout << "-----Stadium Name: " << tempStadiumVector[i].getName() << std::endl;
        std::cout << "-Seating Capacity: " << tempStadiumVector[i].getSeatCap() << std::endl;
        std::cout << "----Team Location: " << tempStadiumVector[i].getLocation() << std::endl;
        std::cout << "--Playing Surface: " << tempStadiumVector[i].surface << std::endl;
        std::cout << "-----------League: " << tempTeamVector[i].league << std::endl;
        std::cout << "------Date opened: " << tempStadiumVector[i].getYearOpened() << std::endl;
        std::cout << "--Distance2CtrFld: " << tempStadiumVector[i].getCenterFieldDist() << std::endl;
        std::cout << "Ballpark typology: " << tempStadiumVector[i].typology << std::endl;
        std::cout << "--------Roof Type: " << tempStadiumVector[i].roof << std::endl;

        tempSouvenirVect = tempStadiumVector[i].getSouvenirs();

        std::cout << "Num. of souvenirs: "<< tempSouvenirVect.size() << std::endl;

        for(const Souvenir& item: tempSouvenirVect)
        {
            std::cout << "---------ID   " << item.getId() << std::endl;
            std::cout << "Is deleted?:  " << item.hidden << std::endl;
            std::cout << "---Souvenir:  " << item.getName() << std::endl;
            std::cout << "------Price:  " << item.getPrice()<< std::endl;
        }
    }
}

Init_classes::~Init_classes()
{

}

void Init_classes::initTestCase()
{

}

void Init_classes::cleanupTestCase()
{

}

void Init_classes::test_case1()
{

}

QTEST_MAIN(Init_classes)

#include "tst_init_classes.moc"
