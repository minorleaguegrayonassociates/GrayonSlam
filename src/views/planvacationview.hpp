#pragma once
#include "src/views/view.hpp"
#include "src/widgets/navbar.hpp"
#include "src/widgets/souvenirlist.hpp"
#include "src/views/souvenirshop.hpp"
#include "src/views/receiptview.hpp"
#include "src/views/mapview.hpp"
#include "src/widgets/stadiumlist.hpp"
#include "src/utils/undirected_graph.hpp"

namespace Ui {
class PlanVacationView;
}

class PlanVacationView : public View
{
    Q_OBJECT

    /* Enum class for each plan type */
    enum PlanType { DijkstraFromAnaheim, ShortestPath, ShortestDistanceFromDetroit, nextClosestStadium, Prims, DFS, BFS, None};
public:
    /* Constructor */
    PlanVacationView(QWidget* parent, NavBar* m_navbar);

    /* Destructor */
    ~PlanVacationView() override;

    /* Reset */
    void resetView() override;

public slots:
    /* Setter */
    void setReceipt(Qtys&);
    void goToNext();
    void activeTrip();
    void goToShop();

     /* Reset */
    void resetUi() override;

private slots:
    void on_Enter_clicked();
    void addToTrip(int);
    void removeFromTrip(int);

    void on_startTrip_clicked();

private:
    Ui::PlanVacationView *m_ui;
    NavBar* m_navbar;
    StadiumList* m_stadiumList;
    StadiumList* m_stadiumListPlanner;
    SouvenirShop* m_souvenirShop;
    ReceiptView* m_receiptViews;
    MapView*    m_mapView;
    double m_distance;
    std::list<int> m_tripList;
    std::vector<Qtys> m_receiptVector;
    int m_previousStadiumId;
    int m_currentStadiumId;
    bool m_printedGrandTotal;
    PlanType m_vacationType;
    std::vector<std::pair<Team,Stadium>> m_planList;
    nstd::undirected_graph<int,int> m_graph;
};

