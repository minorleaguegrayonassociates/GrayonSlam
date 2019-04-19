#include "stadiumlist.hpp"

StadiumList::StadiumList(QWidget *parent) :
    QWidget(parent)
{
    m_listDisplay = new QTableWidget(this);
}
StadiumList::StadiumList(const std::vector<Stadium>& stadiumList, QWidget *parent) :
    QWidget(parent)
{

    for(Stadium stadium : stadiumList)
    {
        m_stadiumList.push_back(stadium.getId());
    }
    m_listDisplay = new QTableWidget(this);
    m_listDisplay->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //To Do Populate table
}
StadiumList::StadiumList(const StadiumList& src, QWidget *parent) :
    QWidget(parent), m_stadiumList(src.m_stadiumList)
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
StadiumList::~StadiumList()
{
    delete m_listDisplay;
}





