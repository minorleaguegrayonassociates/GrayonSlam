#include "stadiumlist.hpp"

/**
 * This constructor constructs a new StadiumList inside of the parent widget and populates it with
 * the information from the database
 * @param parent pointer to parent widget
 */
StadiumList::StadiumList(QWidget* parent) :
    QWidget(parent)
{
    //creates new tree widget
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());
    //populates the tree widget from the database
    populateWidget(Database::getTeamsAndStadiums());
    //sets up the stadium clicked signal
    QObject::connect(m_listDisplay, SIGNAL(itemClicked(QTreeWidgetItem*, int)),this, SLOT(connectWidgetItemToStadium(QTreeWidgetItem*)));
}

/**
 * This constructor constructs a new Stadium List inside of the parent widget and populates it
 * with the information from the given vector
 * @param stadiumList vector containing information to populate Stadium List with
 * @param parent pointer to the parent widet
 */
StadiumList::StadiumList(const std::vector<std::pair<Team,Stadium>>& stadiumList, QWidget *parent) :
    QWidget(parent)
{
    //creates new tree widget
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());
    //populates the widget from the vector of teams and stadiums
    populateWidget(stadiumList);
    //sets up the stadium clicked signal
    QObject::connect(m_listDisplay, SIGNAL(itemClicked(QTreeWidgetItem*, int)),this, SLOT(connectWidgetItemToStadium(QTreeWidgetItem*)));
}

/**
 * setStadiumTeamList resets the tree widget and populates it with the information from the vector passed in
 * @param stadiumList information to repopulate the tree widget with
 */
void StadiumList::setStadiumTeamList(const std::vector<std::pair<Team,Stadium>>& stadiumList)
{
    populateWidget(stadiumList);
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
       emit StadiumClicked(itemS->getStadiumId());
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
    m_listDisplay->clear();
    m_listDisplay->setColumnCount(10);
    QStringList headers = { "Team Name", "League", "Stadium Name", "Location", "Date Opened",
    "Seating Capacity", "Typology", "Roof Type", "Playing Surface", "Distance to Center Field"};
    m_listDisplay->setHeaderLabels(headers);
    for(std::pair<Team,Stadium> stadiumAndTeam : stadiumsAndTeams)
    {
        if(stadiumAndTeam.first.getId() != -1 && stadiumAndTeam.second.getId() != -1)
        {
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
    }
    //Does not allow users to edit the cells directly
    m_listDisplay->setSortingEnabled(true);
    m_listDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

/**
 * This function takes in a string and comma separates the characters into groups of three
 * @param strCpy the string to comma separate
 * @return the comma separated string
 */
std::string StadiumList::commaSeparate(const std::string & strCpy)
{
    std::string commaSeparated = strCpy;

    unsigned int commaCount = 0;
    //loop through entire string
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
