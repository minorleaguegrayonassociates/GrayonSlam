#include "stadiumlist.hpp"

StadiumList::StadiumList(QWidget *parent) :
    QWidget(parent)
{
    m_listDisplay = new QTableWidget(this);
}
StadiumList::StadiumList(const std::vector<int>& teamList, const std::vector<int>& stadiumList, QWidget *parent) :
    QWidget(parent),  m_stadiumList(stadiumList), m_teamList(teamList)
{
    m_listDisplay = new QTableWidget(this);
    //To Do Populate table
}
StadiumList::StadiumList(const StadiumList& src, QWidget *parent) :
    QWidget(parent), m_stadiumList(src.m_stadiumList), m_teamList(src.m_teamList)
{
    m_listDisplay = new QTableWidget(this);

    //To Do Populate table
}
std::vector<int>& StadiumList::getStadiumList()
{
    return m_stadiumList;
}
void StadiumList::setStadiumList(const std::vector<int>& stadiumList)
{
    m_stadiumList = stadiumList;
}
std::vector<int>& StadiumList::getTeamList()
{
    return m_teamList;
}
void StadiumList::setTeamList(const std::vector<int>& teamList)
{
   m_teamList = teamList;
}
StadiumList::~StadiumList()
{
    delete m_listDisplay;
}





