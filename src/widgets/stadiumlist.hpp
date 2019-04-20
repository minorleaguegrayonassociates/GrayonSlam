#ifndef STADIUMLIST_HPP
#define STADIUMLIST_HPP

#include <QMainWindow>
#include <QTreeWidget>
#include "src/datastore/stadium.hpp"
#include "src/datastore/team.hpp"
#include "src/datastore/database.hpp"
#include "src/utils/enumtools.hpp"
#include "stadiumlistitem.hpp"


class StadiumList : public QWidget
{
    Q_OBJECT
public:
    /* Constructors*/
    explicit StadiumList(QWidget *parent = nullptr);
    explicit StadiumList(const std::vector<std::pair<Team,Stadium>>&, QWidget *parent = nullptr);

    /* Resets */
    void setStadiumTeamList(const std::vector<std::pair<Team,Stadium>>&);

    /* Destructor*/
    virtual ~StadiumList();

signals:

public slots:
private:
    /* Helper Functions*/
    void populateWidget(const std::vector<std::pair<Team,Stadium>>&);
    std::string commaSeparate(const std::string&);

    /* Member variables*/
    QTreeWidget* m_listDisplay;
};

#endif // STADIUMLIST_HPP
