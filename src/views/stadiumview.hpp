#pragma once

#include <QWidget>
#include "view.hpp"
#include "src/widgets/stadiumlist.hpp"
#include "src/datastore/database.hpp"


namespace Ui {
class StadiumView;
}

class StadiumView : public View
{
    Q_OBJECT

public:
    explicit StadiumView(QWidget* parent = nullptr);
    ~StadiumView() override;
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
    enum DisplayType
    {
      ALL_STADIUMS,
      ROOF_TYPE,
      AMERICAN_LEAGUE,
      NATIONAL_LEAGUE,
      GREATEST_DISTANCE,
      SHORTEST_DISTANCE
    };
    Ui::StadiumView* ui;
    StadiumList* m_stadiumList;
    DisplayType m_displayStatus;
};
