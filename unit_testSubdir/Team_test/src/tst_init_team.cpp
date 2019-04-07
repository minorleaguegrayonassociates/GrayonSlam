#include <QtTest>
#include <QCoreApplication>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "./../../GrayonSlam/src/datastore/team.hpp"

std::string randomString(int length)
{
    std::string string;

    for(int i = 0; i < length; i++)
        string += rand() % ('Z' - 'A') + 'A';

    return string;
}

// add necessary includes here

class init_team : public QObject
{
Q_OBJECT

public:
init_team();
~init_team();

private slots:
void initTestCase();
void cleanupTestCase();
void test_case1();

};

init_team::init_team()
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
}

init_team::~init_team()
{

}

void init_team::initTestCase()
{

}

void init_team::cleanupTestCase()
{

}

void init_team::test_case1()
{

}

QTEST_MAIN(init_team)

#include "tst_init_team.moc"
