#include "stadiumview.hpp"
#include "ui_stadiumview.h"

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

    m_stadiumList->populateWidget(list);
    ui->TotalStadiumsLabel->setText(QString("Total Amount Of Teams/Stadiums: ") + QString::fromStdString(std::to_string(list.size())));
    ui->TotalSeatingCapacityLabel->setText(QString("Total Seating Capacity: ") + QString::fromStdString(std::to_string(totalSeatingCapacity)));
}

void StadiumView::onStadiumClicked(int stadiumId)
{
    Stadium stadium = Database::findStadiumById(stadiumId);

}

void StadiumView::on_AllStadiumsAndTeamsButton_clicked()
{
    m_displayStatus = ALL_STADIUMS;
    resetUi();
}

void StadiumView::on_AmericanLeagueButton_clicked()
{
    m_displayStatus =AMERICAN_LEAGUE;
    resetUi();
}

void StadiumView::on_NationalLeagueButton_clicked()
{
    m_displayStatus = NATIONAL_LEAGUE;
    resetUi();
}

void StadiumView::on_OpenRoofsButton_clicked()
{
    m_displayStatus = ROOF_TYPE;
    resetUi();
}

void StadiumView::on_GreatestDistButton_clicked()
{
    m_displayStatus = GREATEST_DISTANCE;
    resetUi();
}

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
