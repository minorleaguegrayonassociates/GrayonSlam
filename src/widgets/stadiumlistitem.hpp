#ifndef STADIUMLISTITEM_HPP
#define STADIUMLISTITEM_HPP

#include <QTreeWidgetItem>
#include "src/datastore/stadium.hpp"
#include "src/datastore/team.hpp"

class StadiumListItem : public QTreeWidgetItem
{
public:
    StadiumListItem(QTreeWidget* parent, const Stadium&, const QStringList&);
    virtual bool operator<(const StadiumListItem&);
    int getStadiumId();
private:
    QTreeWidget* parent;
    int m_seatCap = -1;
    int m_yearOpened = -1;
    int m_centerFieldDist = -1;
    int m_stadiumId = -1;

};

#endif // STADIUMLISTITEM_HPP
