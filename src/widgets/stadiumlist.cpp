#include "stadiumlist.hpp"

StadiumList::StadiumList(QWidget *parent) :
    QWidget(parent)
{
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());
    populateWidget(Database::getTeamsAndStadiums());
}

StadiumList::StadiumList(const std::vector<std::pair<Team,Stadium>>& stadiumList, QWidget *parent) :
    QWidget(parent)
{
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());
    populateWidget(stadiumList);
}

void StadiumList::setStadiumTeamList(const std::vector<std::pair<Team,Stadium>>& stadiumList)
{
    populateWidget(stadiumList);
}

StadiumList::~StadiumList()
{
    delete m_listDisplay;
}

void StadiumList::populateWidget(const std::vector<std::pair<Team,Stadium>>& stadiumsAndTeams)
{
    //clears old display
    m_listDisplay->clear();
    m_listDisplay->setColumnCount(10);
    QStringList headers = { "Team Name", "League", "Stadium Name", "Location", "Date Opened",
            "Seating Capacity", "Typology", "Roof Type", "Playing Surface",
             "Distance to Center Field"};
    m_listDisplay->setHeaderLabels(headers);
    for(std::pair<Team,Stadium> stadiumAndTeam : stadiumsAndTeams)
    {

        if(stadiumAndTeam.first.getId() != -1 && stadiumAndTeam.second.getId() != -1)
        {

            //Adds Qstrings for the stadium list item
            QStringList tmpList;
            tmpList.push_back(QString::fromStdString(stadiumAndTeam.first.getName()));
            tmpList.push_back(QString::fromStdString(stadiumAndTeam.first.LEAGUE_STRING[stadiumAndTeam.first.league]));
            tmpList.push_back(QString::fromStdString(stadiumAndTeam.second.getName()));
            tmpList.push_back(QString::fromStdString(stadiumAndTeam.second.getLocation()));
            tmpList.push_back(QString::fromStdString(std::to_string(stadiumAndTeam.second.getYearOpened())));
            tmpList.push_back(QString::fromStdString(commaSeparate(std::to_string(stadiumAndTeam.second.getSeatCap()))));
            tmpList.push_back(QString::fromStdString(stadiumAndTeam.second.TYPOLOGY_STRING[stadiumAndTeam.second.typology]));
            tmpList.push_back(QString::fromStdString(stadiumAndTeam.second.ROOF_STRING[stadiumAndTeam.second.roof]));
            tmpList.push_back(QString::fromStdString(stadiumAndTeam.second.SURFACE_STRING[stadiumAndTeam.second.surface]));
            tmpList.push_back(QString::fromStdString(commaSeparate(std::to_string(stadiumAndTeam.second.getCenterFieldDist()))));
            new StadiumListItem(m_listDisplay,stadiumAndTeam.second,tmpList);
        }
    }

    //Does not allow users to edit the cells directly
    m_listDisplay->setSortingEnabled(true);
    m_listDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

std::string StadiumList::commaSeparate(const std::string & strCpy)
{
    std::string commaSeparated = strCpy;

    unsigned int commaCount = 0;
    for(unsigned int index = commaSeparated.length(); index != 0; --index)
    {
        //checks to see if group of 3
        if((commaSeparated.length() - index - commaCount)%3 == 0 && index != commaSeparated.length())
        {
            commaSeparated.insert(index, 1, ',');
            ++commaCount;
        }
    }

    return commaSeparated;

}




