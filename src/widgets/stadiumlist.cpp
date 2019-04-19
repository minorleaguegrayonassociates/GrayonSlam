#include "stadiumlist.hpp"

StadiumList::StadiumList(QWidget *parent) :
    QWidget(parent)
{
    m_listDisplay = new QTableWidget(this);
}
StadiumList::StadiumList(const std::vector<Stadium>& stadiumList, const std::vector<Team>& teamList, QWidget *parent) :
    QWidget(parent)
{

    for(Stadium stadium : stadiumList)
    {
        m_stadiumList.push_back(stadium.getId());
    }
    for(Team team : teamList)
    {
        m_teamList.push_back(team.getId());
    }
    m_listDisplay = new QTableWidget(this);
    m_listDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //To Do Populate table
}
StadiumList::StadiumList(const StadiumList& src, QWidget *parent) :
    QWidget(parent), m_stadiumList(src.m_stadiumList), m_teamList(src.m_teamList)
{
    m_listDisplay = new QTableWidget(this);

    //Does not allow users to edit the cells directly
    m_listDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //To Do Populate table
}
std::vector<int>& StadiumList::getStadiumList()
{
    return m_stadiumList;
}
void StadiumList::setStadiumList(const std::vector<Stadium>& stadiumList)
{
    m_stadiumList.clear();
    for(Stadium stadium : stadiumList)
    {
        m_stadiumList.push_back(stadium.getId());
    }
}
std::vector<int>& StadiumList::getTeamList()
{
    return m_teamList;
}
void StadiumList::setTeamList(const std::vector<Team>& teamList)
{
    m_teamList.clear();
    for(Team team : teamList)
    {
        m_teamList.push_back(team.getId());
    }
}
StadiumList::~StadiumList()
{
    delete m_listDisplay;
}





