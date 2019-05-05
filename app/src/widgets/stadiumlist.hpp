#pragma once
#include <QTreeWidget>
#include "src/datastore/database.hpp"
#include "stadiumlistitem.hpp"
#include "src/utils/stringfunctions.hpp"

/**
 * @brief StadiumList class
 *
 * Provides a simple way to list data about stadiums and teams.
 * This list isn't tied to the database. It only displays the contents of what is given to it.
 *
 * To use:
 * @code{.cpp}
 * StadiumList* list = new StadiumList(widget);
 * list->setStadiumTeamList(stadiumTeamVector);
 * @endcode
 *
 * This will create a stadium list within its parent widget.
 * Then it will add all the stadiums and teams from the vector to the list for displaying.
 */
class StadiumList : public QWidget
{
    Q_OBJECT
public:
    /* Constructors*/
    explicit StadiumList(QWidget* parent = nullptr);
    explicit StadiumList(const std::vector<std::pair<Team,Stadium>>&, QWidget* parent = nullptr);

    /* Setters */
    void setSorting(bool);

    /* Resets */
    void populateWidget(const std::vector<std::pair<Team,Stadium>>&);
    void allowHidden(bool);
    void clear();

    /* Destructor*/
    ~StadiumList() override;

signals:
    /* Clicked Signal*/
    void stadiumClicked(int stadiumId);

private slots:
    /* Internal slots*/
    void connectWidgetItemToStadium(QTreeWidgetItem*);

private:
    /* Member variables*/
    QTreeWidget* m_listDisplay;
    bool m_showHidden;
    bool sortingStatus;
};
