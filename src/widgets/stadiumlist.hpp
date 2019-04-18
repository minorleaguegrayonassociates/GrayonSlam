#ifndef STADIUMLIST_HPP
#define STADIUMLIST_HPP

#include <QMainWindow>
#include "src/datastore/stadium.hpp"
#include "src/datastore/team.hpp"

class StadiumList
{
    Q_OBJECT
public:
    explicit StadiumList();
    StadiumList(const std::vector<Stadium>&);
    std::vector<Stadium>& getStadiumList();
    void setStadiumList(const std::vector<Stadium>&);
    StadiumList(const StadiumList&);
    virtual ~StadiumList();

signals:

public slots:
private:
    std::vector<Stadium> m_stadiumList;
};

#endif // STADIUMLIST_HPP
