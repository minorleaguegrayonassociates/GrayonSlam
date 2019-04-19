#include "stadiumlist.hpp"

StadiumList::StadiumList(QWidget *parent) :
    QWidget(parent)
{
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());

}

StadiumList::StadiumList(const std::vector<std::pair<Team,Stadium>>& stadiumList, QWidget *parent) :
    QWidget(parent)
{

    for(std::pair<Team,Stadium> stadiumId : stadiumList)
    {
        m_stadiumList.push_back(stadiumId.second.getId());
    }
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());
    populateWidget();
}

StadiumList::StadiumList(const StadiumList& src, QWidget *parent) :
    QWidget(parent), m_stadiumList(src.m_stadiumList)
{
    m_listDisplay = new QTreeWidget(this);
    m_listDisplay->resize(parent->size());
    populateWidget();
}

std::vector<int>& StadiumList::getStadiumList()
{
    return m_stadiumList;
}

void StadiumList::setStadiumList(const std::vector<std::pair<Team,Stadium>>& stadiumList)
{
    m_stadiumList.clear();
    for(std::pair<Team,Stadium> stadium : stadiumList)
    {
        m_stadiumList.push_back(stadium.second.getId());
    }
    populateWidget();
}

StadiumList::~StadiumList()
{
    delete m_listDisplay;
}

void StadiumList::populateWidget()
{
    m_listDisplay->clear();
    m_listDisplay->setColumnCount(10);
    QStringList headers = { "Team Name", "League", "Stadium Name", "Location", "Date Opened",
            "Seating Capacity", "Typology", "Roof Type", "Playing Surface",
             "Distance to Center Field"};
    m_listDisplay->setHeaderLabels(headers);

    for(int id:m_stadiumList)
    {
        Stadium tmp = Database::getStadiums()[id];
        QStringList tmpList;
        tmpList.push_back(QString::fromStdString(tmp.getName()));
        new QTreeWidgetItem(m_listDisplay,tmpList);
    }

    //Does not allow users to edit the cells directly
    m_listDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);

}




