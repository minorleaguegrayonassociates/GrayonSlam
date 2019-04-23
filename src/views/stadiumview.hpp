#pragma once

#include <QWidget>
#include "view.hpp"
#include "src/widgets/stadiumlist.hpp"
#include "src/datastore/database.hpp"


namespace Ui {
class StadiumView;
}

/**
 *@class StadiumView class
 *
 * This class is used for displaying the information in the database
 * in various different ways. It can display all teams and stadiums,
 * National/American league teams only, etc.
 *
 * This class keeps track of what is being displayed as a call
 * to resetUi will make sure that the tree widget gets repopulated,
 * but to whatever the last button clicked was
 *
 * Note:
 * This view assumes that the database is initialized with data for it to read out of.
 */
class StadiumView : public View
{
    Q_OBJECT

public:
    /* Constructor*/
    explicit StadiumView(QWidget* parent = nullptr);

    /* Destructor*/
    ~StadiumView() override;

    /* Resets */
    void resetView() override;
    void resetUi() override;

    /* Find Max/Min Distance Teams */
    std::vector<std::pair<Team,Stadium>> maxDistanceTeams(std::vector<std::pair<Team,Stadium>>);
    std::vector<std::pair<Team,Stadium>> minDistanceTeams(std::vector<std::pair<Team,Stadium>>);

private slots:
    void onStadiumClicked(int);

    void on_AllStadiumsAndTeamsButton_clicked();

    void on_AmericanLeagueButton_clicked();

    void on_NationalLeagueButton_clicked();

    void on_OpenRoofsButton_clicked();

    void on_GreatestDistButton_clicked();

    void on_ShortestDistButton_clicked();

private:
    /**
     * @enum DisplayType
     *
     * This enum store the information of what is being
     * displayed inside the Stadium List. i.e. The last clicked button inside
     * the view's action is stored as an enum of this type.
     */
    enum DisplayType
    {
      ALL_STADIUMS,
      ROOF_TYPE,
      AMERICAN_LEAGUE,
      NATIONAL_LEAGUE,
      GREATEST_DISTANCE,
      SHORTEST_DISTANCE
    };

    /* Data Members */
    Ui::StadiumView* ui;
    StadiumList* m_stadiumList;
    DisplayType m_displayStatus;
};
