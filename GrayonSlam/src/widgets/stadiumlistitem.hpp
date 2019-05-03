#pragma once

#include <QTreeWidgetItem>
#include "src/datastore/stadium.hpp"

class StadiumListItem : public QTreeWidgetItem
{
public:
    /* Constructor */
    StadiumListItem(QTreeWidget* parent, const Stadium&, const QStringList&);

    /* Operator Overloads*/
    virtual bool operator<(const StadiumListItem&);

    /* Getters */
    int getStadiumId();

private:
    /* Data Members */
    QTreeWidget* parent;
    int m_seatCap = -1;
    int m_yearOpened = -1;
    int m_centerFieldDist = -1;
    int m_stadiumId = -1;

};
