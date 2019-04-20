#include "stadiumlistitem.hpp"

StadiumListItem::StadiumListItem(QTreeWidget* parent, const Stadium& stadium, const QStringList& strings): QTreeWidgetItem (parent, strings), parent(parent)
{
    m_seatCap = stadium.getSeatCap();
    m_yearOpened = stadium.getYearOpened();
    m_centerFieldDist = stadium.getCenterFieldDist();

}
bool StadiumListItem::operator<(const StadiumListItem& otherItem)
{
    bool lessThan;
    //compare date opened
    if(parent->sortColumn() == 4)
    {
        lessThan = m_yearOpened < otherItem.m_yearOpened;
    }
    //compare seating capacity
    else if(parent->sortColumn() == 5)
    {
        lessThan = m_seatCap < otherItem.m_seatCap;
    }
    //compare distance to center field
    else if(parent->sortColumn() == 9)
    {
        lessThan = m_centerFieldDist < otherItem.m_centerFieldDist;
    }
    //compare string and not a number
    else
    {
        lessThan = QTreeWidgetItem::operator<(otherItem);
    }
    return lessThan;
}
