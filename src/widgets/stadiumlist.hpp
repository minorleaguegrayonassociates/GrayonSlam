#ifndef STADIUMLIST_HPP
#define STADIUMLIST_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include "src/datastore/stadium.hpp"
#include "src/datastore/team.hpp"
#include "src/datastore/database.hpp"


class StadiumList : public QWidget
{
    Q_OBJECT
public:
    explicit StadiumList(QWidget *parent = nullptr);
    explicit StadiumList(const std::vector<std::pair<Team,Stadium>>&, QWidget *parent = nullptr);
    StadiumList(const StadiumList&, QWidget *parent = nullptr);
    std::vector<int>& getStadiumList();
    void setStadiumList(const std::vector<std::pair<Team,Stadium>>&);
    virtual ~StadiumList();

signals:

public slots:
private:
    /* Helper Functions*/
    void populateWidget();

    /* Member variables*/
    std::vector<int> m_stadiumList;
    QTreeWidget* m_listDisplay;
};

#endif // STADIUMLIST_HPP
