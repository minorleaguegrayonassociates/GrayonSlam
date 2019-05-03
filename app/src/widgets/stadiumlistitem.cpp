#include "stadiumlistitem.hpp"

/**
 * This constructor constructs a StadiumListItem and puts it into the parent Tree Widget
 * @param parent Parent tree widget of the StadiumListItem
 * @param stadium Stadium that corresponds the the row
 * @param strings A QStringList used to populate the QTreeWidget
 */
StadiumListItem::StadiumListItem(QTreeWidget* parent, const Stadium& stadium, const QStringList& strings): QTreeWidgetItem (parent, strings), parent(parent)
{
    m_seatCap = stadium.getSeatCap();
    m_yearOpened = stadium.getYearOpened();
    m_centerFieldDist = stadium.getCenterFieldDist();
    m_stadiumId = stadium.getId();

}

/**
 * operator< is overloaded to compare the numerical values, and if it is not numerical, does
 * a lexigraphical comparison instead
 * @param otherItem The StadiumListItem being compare with
 * @return A boolean that specifies a ordering relation between the items
 */
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

/**
 * A getter that returns the stadium Id of the StadiumListItem
 * @return
 */
int StadiumListItem::getStadiumId()
{
    return m_stadiumId;
}
