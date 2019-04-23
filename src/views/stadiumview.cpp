#include "stadiumview.hpp"
#include "ui_stadiumview.h"
#include <QMessageBox>

/**
 * Constructs a Stadium View with a pointer to the parent widget which it will reside in
 *
 * @param parent pointer to widget it will reside in
 */
StadiumView::StadiumView(QWidget* parent) :
    View(parent),
    ui(new Ui::StadiumView),
     m_displayStatus(ALL_STADIUMS)
{
    //Initialize Ui
    ui->setupUi(this);

    //Instantiate and populate tree widget
    m_stadiumList = new StadiumList(ui->stadiumList);
    resetUi();
    connect(m_stadiumList, &StadiumList::stadiumClicked, this, &StadiumView::onStadiumClicked);
}

/**
 * Destructor deletes the Ui and the tree widget
 */
StadiumView::~StadiumView()
{
    delete ui;
    delete m_stadiumList;
}

/**
 * resetView() clears all of its children and repopulates the widgets
 * from the database
 */
void StadiumView::resetView()
{
    //clear all data, get it new from database, and populate table
    m_displayStatus = ALL_STADIUMS;
    resetUi();
}

/**
 * resetUi() repopulates the tree widget from the database
 */
void StadiumView::resetUi()
{
    //clear table and repopulate it with list
    std::vector<std::pair<Team,Stadium>> list;
    std::vector<std::pair<Team,Stadium>> listT = Database::getTeamsAndStadiums();
    int totalSeatingCapacity = 0;

    //Check to see what needs to be displayed in the list
    switch(m_displayStatus)
    {
        case ROOF_TYPE:
            for(unsigned int index = 0; index < listT.size(); ++index)
            {
                if(listT[index].second.roof == Stadium::OPEN)
                {
                    list.push_back(listT[index]);
                    totalSeatingCapacity +=  listT[index].second.getSeatCap();
                }
             }
             break;

        case AMERICAN_LEAGUE:
            for(unsigned int index = 0; index < listT.size(); ++index)
            {
                if(listT[index].first.league == Team::AMERICAN)
                {
                    list.push_back(listT[index]);
                    totalSeatingCapacity +=  listT[index].second.getSeatCap();
                }
             }
            break;

        case NATIONAL_LEAGUE:
            for(unsigned int index = 0; index < listT.size(); ++index)
            {
                if(listT[index].first.league == Team::NATIONAL)
                {
                    list.push_back(listT[index]);
                    totalSeatingCapacity +=  listT[index].second.getSeatCap();
                }
             }
            break;

        case GREATEST_DISTANCE:
            list = maxDistanceTeams(Database::getTeamsAndStadiums());
            for(unsigned int index = 0; index < list.size(); ++index)
            {
                    totalSeatingCapacity +=  list[index].second.getSeatCap();
            }
            break;

        case SHORTEST_DISTANCE:
            list = minDistanceTeams(Database::getTeamsAndStadiums());
            for(unsigned int index = 0; index < list.size(); ++index)
            {
                    totalSeatingCapacity +=  list[index].second.getSeatCap();
            }
            break;

        case ALL_STADIUMS:
            list = listT;
            for(unsigned int index = 0; index < list.size(); ++index)
            {
                    totalSeatingCapacity +=  list[index].second.getSeatCap();
            }
            break;
    }

    //populate the widget from the list that corresponds to the button clicked
    m_stadiumList->populateWidget(list);

    //Set labels to reflect what is in list
    ui->TotalStadiumsLabel->setText(QString("Total Amount Of Teams/Stadiums: ") + QString::fromStdString(std::to_string(list.size())));
    ui->TotalSeatingCapacityLabel->setText(QString("Total Seating Capacity: ") + QString::fromStdString(std::to_string(totalSeatingCapacity)));
}

/**
 * onStadiumClicked is a slot that displays the given stadium and
 * corresponding team information inside a QMessageBox when a signal
 * that emits stadiums id's is connected to it.
 *
 * @param stadiumId Id of stadium to display.
 */
void StadiumView::onStadiumClicked(int stadiumId)
{
    Stadium stadium = Database::findStadiumById(stadiumId);
    Team team = Database::findTeamById(stadium.getTeamId());

    //Don't question the spaces, it is to deal with message box not treating spaces the same width as a character
    std::string msg;
    msg = std::string("\tTeam Information\n")
         +std::string("Team Name:            ") + team.getName() + '\n'
         +std::string("League:                     ") + team.LEAGUE_STRING[team.league] + '\n'
         +std::string("Stadium Name:       ") + stadium.getName() + '\n'
         +std::string("Location:                  ") + stadium.getLocation() + '\n'
         +std::string("Year Opened:           ") + std::to_string(stadium.getYearOpened()) + '\n'
         +std::string("Seating Capacity:    ") + StadiumList::commaSeparate(std::to_string(stadium.getSeatCap())) + '\n'
         +std::string("Typology:                 ") + stadium.TYPOLOGY_STRING[stadium.typology] + '\n'
         +std::string("Roof Type:                ") + stadium.ROOF_STRING[stadium.roof] + '\n'
         +std::string("Playing Surface:       ") + stadium.SURFACE_STRING[stadium.surface] + '\n'
         +std::string("Dist To Cntr Field:    ") + StadiumList::commaSeparate(std::to_string(stadium.getCenterFieldDist())) + '\n';
    QMessageBox box;
    box.setText(QString::fromStdString(msg));
    box.setStandardButtons(QMessageBox::Close);
    box.exec();
}

/**
 * When on_AllStadiumsAndTeamsButton_clicked is called, the stadium list is cleared
 * and repopulated with all stadiums and teams from the database and the labels below
 * are updated to match it.
 */
void StadiumView::on_AllStadiumsAndTeamsButton_clicked()
{
    m_displayStatus = ALL_STADIUMS;
    resetUi();
}

/**
 * When on_AmericanLeagueButton_clicked is called, the stadium list is cleared
 * and repopulated with only American League teams and the labels below
 * are updated to match it.
 */
void StadiumView::on_AmericanLeagueButton_clicked()
{
    m_displayStatus =AMERICAN_LEAGUE;
    resetUi();
}

/**
 * When on_NationalLeagueButton_clicked is called, the stadium list is cleared
 * and repopulated with only National League teams and the labels below
 * are updated to match it.
 */
void StadiumView::on_NationalLeagueButton_clicked()
{
    m_displayStatus = NATIONAL_LEAGUE;
    resetUi();
}

/**
 * When on_OpenRoofsButton_clicked is called, the stadium list is cleared
 * and repopulated with only stadiums with open roofs and the labels below
 * are updated to match it.
 */
void StadiumView::on_OpenRoofsButton_clicked()
{
    m_displayStatus = ROOF_TYPE;
    resetUi();
}

/**
 * When on_GreatestDistButton_clicked is called, the stadium list is cleared
 * and repopulated with only the teams that have the greatest distance to center field
 * and the labels below are updated to match it.
 */
void StadiumView::on_GreatestDistButton_clicked()
{
    m_displayStatus = GREATEST_DISTANCE;
    resetUi();
}

/**
 * When on_ShortesttDistButton_clicked is called, the stadium list is cleared
 * and repopulated with only the teams that have the shortest distance to center field
 * and the labels below are updated to match it.
 */
void StadiumView::on_ShortestDistButton_clicked()
{
    m_displayStatus = SHORTEST_DISTANCE;
    resetUi();
}


/**
 * Given a list of team and stadium pairs, this function will find the stadiums with the max
 * distances to center field and populate a vector with them
 *
 * @param list a vector of team and stadium pairs
 * @return A vector containing a set of pairs containing max dist to center field
 */
std::vector<std::pair<Team,Stadium>> StadiumView::maxDistanceTeams(std::vector<std::pair<Team,Stadium>> list)
{
    std::vector<std::pair<Team,Stadium>> stadiumsWithMaxDistance;
    int maxDistance = -1;
    for(std::pair<Team,Stadium> teamAndStadium: list)
    {
        int dist = teamAndStadium.second.getCenterFieldDist();
        if(dist > maxDistance)
        {
            maxDistance = dist;
        }
    }
    for(std::pair<Team,Stadium> teamAndStadium: list)
    {
        int dist = teamAndStadium.second.getCenterFieldDist();
        if(dist == maxDistance)
        {
            stadiumsWithMaxDistance.push_back(teamAndStadium);
        }
    }
    return stadiumsWithMaxDistance;
}


/**
 * Given a list of team and stadium pairs, this function will find the stadiums with the min
 * distances to center field and populate a vector with them
 *
 * @param list a vector of team and stadium pairs
 * @return A vector containing a set of pairs containing min dist to center field
 */
std::vector<std::pair<Team,Stadium>> StadiumView::minDistanceTeams(std::vector<std::pair<Team,Stadium>> list)
{
    std::vector<std::pair<Team,Stadium>> stadiumsWithMinDistance;
    int minDistance = std::numeric_limits<int>::max();
    for(std::pair<Team,Stadium> teamAndStadium: list)
    {
        int dist = teamAndStadium.second.getCenterFieldDist();
        if(dist < minDistance)
        {
            minDistance = dist;
        }
    }
    for(std::pair<Team,Stadium> teamAndStadium: list)
    {
        int dist = teamAndStadium.second.getCenterFieldDist();
        if(dist == minDistance)
        {
            stadiumsWithMinDistance.push_back(teamAndStadium);
        }
    }
    return stadiumsWithMinDistance;
}
