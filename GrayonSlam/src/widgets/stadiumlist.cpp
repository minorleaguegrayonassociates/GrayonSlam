#include "stadiumlist.hpp"

/**
 * This constructor constructs a new StadiumList inside of the parent widget and populates it with
 * the information from the database
 * @param parent pointer to parent widget
 */
StadiumList::StadiumList(QWidget* parent)
    : StadiumList(Database::getTeamsAndStadiums(), parent)
{}

/**
 * This constructor constructs a new Stadium List inside of the parent widget and populates it
 * with the information from the given vector
 * @param stadiumList vector containing information to populate Stadium List with
 * @param parent pointer to the parent widet
 */
StadiumList::StadiumList(const std::vector<std::pair<Team,Stadium>>& stadiumList, QWidget* parent) :
    QWidget(parent), m_showHidden(false)
{
    //creates new tree widget
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());
    //populates the widget from the vector of teams and stadiums
    populateWidget(stadiumList);
    //sets up the stadium clicked signal
    connect(m_listDisplay, &QTreeWidget::itemClicked, this, &StadiumList::connectWidgetItemToStadium);
}

/**
 * The destructor deletes the tree widget
 */
StadiumList::~StadiumList()
{
    delete m_listDisplay;
}

/**
 * ConnectWidgetItemToStadium takes the item clicked signal and converts it the emit the stadium id
 * @param item The item that was clicked on in the tree widget
 */
void StadiumList::connectWidgetItemToStadium(QTreeWidgetItem* item)
{
    StadiumListItem* itemS = dynamic_cast<StadiumListItem*>(item);
    if(itemS != nullptr)
    {
       emit stadiumClicked(itemS->getStadiumId());
    }
}

/**
 * populateWidget() takes a vector of stadiums and teams, converts their data to QStrings, and inserts
 * them into the Tree Widget
 * @param stadiumsAndTeams vector containing stadiums and teams
 */
void StadiumList::populateWidget(const std::vector<std::pair<Team,Stadium>>& stadiumsAndTeams)
{
    //clears old display
    clear();
    m_listDisplay->setColumnCount(10);
    QStringList headers = { "Team Name", "League", "Stadium Name", "Location", "Date Opened",
    "Seating Capacity", "Typology", "Roof Type", "Playing Surface", "Distance to Center Field"};
    m_listDisplay->setHeaderLabels(headers);
    m_listDisplay->setSortingEnabled(false);
    for(std::pair<Team,Stadium> stadiumAndTeam : stadiumsAndTeams)
    {
        if(m_showHidden && stadiumAndTeam.second.hidden){continue;}
        //Adds all fields from stadium and team to the tree widget by converting them Qstrings
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

        //Constructs a new stadium list item and adds it to the tree widget
        new StadiumListItem(m_listDisplay,stadiumAndTeam.second,tmpList);
    }
    //Does not allow users to edit the cells directly
    m_listDisplay->setSortingEnabled(true);
    m_listDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/**
 * allowHidden(bool) changes the status of the stadium list to (not) display hidden teams/stadiums
 * depending on the value of the boolean
 *
 * Note: This does not change the stadiums or teams that are currently in the list. It only affects the list
 * upon population of the list
 *
 * @param hidden boolean that tells widget to display the hidden stadiums/teams or not
 */
void StadiumList::allowHidden(bool hidden)
{
    m_showHidden = hidden;
}

/**
 * clear() clears the contents of the stadium list of all data
 */
void StadiumList::clear()
{
    m_listDisplay->clear();
}
