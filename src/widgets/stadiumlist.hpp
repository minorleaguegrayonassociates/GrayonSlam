#ifndef STADIUMLIST_HPP
#define STADIUMLIST_HPP

#include <QMainWindow>
#include <QTableWidget>
#include "src/datastore/stadium.hpp"
#include "src/datastore/team.hpp"

class StadiumList : public QWidget
{
    Q_OBJECT
public:
    explicit StadiumList(QWidget *parent = nullptr);
    StadiumList(const std::vector<Stadium>&,QWidget *parent = nullptr);
    StadiumList(const StadiumList&,QWidget *parent = nullptr);
    std::vector<Stadium>& getStadiumList();
    void setStadiumList(const std::vector<Stadium>&);
    virtual ~StadiumList();

signals:

public slots:
private:
    std::vector<Stadium> m_stadiumList;
    QTableWidget* m_listDisplay;
};

#endif // STADIUMLIST_HPP
