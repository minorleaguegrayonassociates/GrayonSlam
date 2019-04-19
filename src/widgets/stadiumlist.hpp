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
    explicit StadiumList(const std::vector<Stadium>&, const std::vector<Team>&, QWidget *parent = nullptr);
    StadiumList(const StadiumList&, QWidget *parent = nullptr);
    std::vector<int>& getStadiumList();
    std::vector<int>& getTeamList();
    void setStadiumList(const std::vector<Stadium>&);
    void setTeamList(const std::vector<Team>&);
    virtual ~StadiumList();

signals:

public slots:
private:
    std::vector<int> m_stadiumList;
    std::vector<int> m_teamList;
    QTableWidget* m_listDisplay;
};

#endif // STADIUMLIST_HPP
