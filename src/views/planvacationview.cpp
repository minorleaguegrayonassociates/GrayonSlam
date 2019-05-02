#include "planvacationview.hpp"
#include "ui_planvacationview.h"
#include "src/datastore/database.hpp"
#include <QDebug>

/* Constructor */
PlanVacationView::PlanVacationView(QWidget *parent, NavBar* bar)
    : View(parent), m_ui(new Ui::PlanVacationView), m_navbar(bar),
      m_previousStadiumId(-1), m_currentStadiumId(-1)
{
    m_ui->setupUi(this);

    /* Initialize stadium list and the stadium list planner - clear the planner before starting */
    m_stadiumList = new StadiumList(m_ui->stadiumListWidget);
    m_stadiumListPlanner = new StadiumList(m_ui->stadiumListPlannerWidget);
    m_stadiumListPlanner->clear();

    /* Initialize views */
    m_souvenirShop = new SouvenirShop(m_ui->activeVacation);
    m_receiptViews = new ReceiptView(m_ui->vacationReceipt);
    m_mapView = new MapView(m_ui->tripMap);

    /* Setting the different options for the QComboBox `vacationType` and their associated values */
    m_ui->vacationType->addItem(tr("--- Vacation Type ---"), PlanVacationView::None);
    m_ui->vacationType->addItem(tr("Dijkstra from Anaheim"), PlanVacationView::DijkstraFromAnaheim);
    m_ui->vacationType->addItem(tr("Shortest path"), PlanVacationView::ShortestPath);
    m_ui->vacationType->addItem(tr("Shortest Distance from Detroit"), PlanVacationView::ShortestDistanceFromDetroit);
    m_ui->vacationType->addItem(tr("Next Closest Stadium"), PlanVacationView::nextClosestStadium);
    m_ui->vacationType->addItem(tr("Prims"), PlanVacationView::Prims);
    m_ui->vacationType->addItem(tr("Depth First Search"), PlanVacationView::DFS);
    m_ui->vacationType->addItem(tr("Breadth First Search"), PlanVacationView::BFS);

    /* Connecting signals to slots */
    connect(m_souvenirShop,&SouvenirShop::goToReceipt, this,&PlanVacationView::setReceipt);
    connect(m_souvenirShop,&SouvenirShop::skipCheckout,this,&PlanVacationView::goToNext);
    connect(m_receiptViews,&ReceiptView::goToNext,this,&PlanVacationView::goToNext);
    connect(m_mapView,&MapView::goToShop,this,&PlanVacationView::goToShop);
    connect(m_ui->ContinueToNext,&QAbstractButton::clicked,this,&PlanVacationView::resetUi);
    connect(m_stadiumList,&StadiumList::stadiumClicked,this,&PlanVacationView::addToTrip);
    connect(m_stadiumListPlanner,&StadiumList::stadiumClicked,this,&PlanVacationView::removeFromTrip);
}

/* Destructor */
PlanVacationView::~PlanVacationView()
{
    delete m_ui;
    delete m_stadiumList;
    delete m_souvenirShop;
    delete m_receiptViews;
    delete m_mapView;
}

/* Resets */
void PlanVacationView::resetView()
{
    m_ui->planVacationStack->setCurrentWidget(m_ui->chooseType);
}

void PlanVacationView::resetUi()
{
    m_navbar->setHidden(false);
    m_previousStadiumId = -1;
    m_currentStadiumId = -1;
    m_ui->planVacationStack->setCurrentWidget(m_ui->chooseType);
    m_ui->vacationType->setCurrentIndex(0);
    m_printedGrandTotal = false;
}

/**
 * This function switches the page on the `planVacationStack`
 * and set's the receipt for `m_receiptViews`
 *
 * @param receipt - Qtys data to print receipt
 */
void PlanVacationView::setReceipt(Qtys& receipt)
{
    m_ui->planVacationStack->setCurrentWidget(m_ui->vacationReceipt);
    m_receiptVector.push_back(receipt);
    m_receiptViews->makeReceipt(receipt,false);
}

/**
 * As long as trip list isn't empty goes to the next stadium
 * otherwise print the grand total
 */
void PlanVacationView::goToNext()
{
    // Store previous Id then removing it from the `tripList`
    m_previousStadiumId  = m_tripList.front();

    /* If the `tripList` isn't already empty, erase the last stadium */
    if(!m_tripList.empty())
        m_tripList.pop_front();

    // Continue with the trip
    PlanVacationView::activeTrip();
}

/**
 * This function takes care of loading in the next stadiumId from `m_tripList`
 * if `m_tripList`is empty then it will print out the grandTotal Receipt if anything
 * was purchased on the trip. Otherwise it will
 */
void PlanVacationView::activeTrip()
{
    /* If the `tripList` isn't empty go to the next stadium, otherwise, if the receiptVector isn't empty
     * print out the grandTotal receipt for all the items bought at each stadium,
     *`resetUi`
     */
    if(!m_tripList.empty())
    {
        /* Set current id, then set `souvenirShop` to the `m_currentStadiumId` */
        m_currentStadiumId = m_tripList.front();
        m_souvenirShop->setCurrentStadiumId(m_currentStadiumId);

        /* If the value of `m_previousStadiumId` has been set then turn stack to `tripMap` and set animation
         * Won't animate when `m_previousStadiumId` hasn't been set (i.e. the first stadium)
         */
        if(m_previousStadiumId != -1)
        {
            m_ui->planVacationStack->setCurrentWidget(m_ui->tripMap);
            m_mapView->setAnimation(m_previousStadiumId,m_currentStadiumId);
        }
    }
    else if(!m_receiptVector.empty())
    {
        /* Will keep track if a grandTotal has been printed to not print total distance afterwards,
         * flips `planVacationStack` page to `vacationReceipt` and prints `grandTotal` then
         * clears `m_receiptVector`
         */
        m_printedGrandTotal = true;
        m_ui->planVacationStack->setCurrentWidget(m_ui->vacationReceipt);
        m_receiptViews->grandTotal(m_receiptVector, m_distance);
        m_receiptVector.clear();
    }
    else if(!m_printedGrandTotal)
    {
        /* If nothing was purchased on the trip this will execute, `planVacationStack` will be set to
         * `vacationDistance` and set's the QLabel `distance` to the miles traveled
         */
        m_ui->planVacationStack->setCurrentWidget(m_ui->vacationDistance);
        m_ui->distance->setText(QString::number(m_distance,'f',2)+" miles");
    }
    else
    {
        // If the trip is done reset
        PlanVacationView::resetUi();
    }
}

/**
 * This function is meant to be connected to a signal
 * from MapView, when goToShop is emited this function
 * set's the `planVacationStack` to `activeVacation`
 */
void PlanVacationView::goToShop()
{
    // Switch `planVacationStack` page to `activeVacation`
    m_ui->planVacationStack->setCurrentWidget(m_ui->activeVacation);
}

/**
 * Set the vacationType and switch `planVacationStack` page
 * to `planVacation` if selection isn't equal to `None`
 */
void PlanVacationView::on_Enter_clicked()
{
    /* Set the vacationType and switch `planVacationStack` page to `planVacation` if selection isn't equal to `None` */
    m_vacationType = static_cast<PlanType>(m_ui->vacationType->currentData().toInt());
    if(m_vacationType != PlanType::None)
    {
        for(auto edge : Database::getDistances())
        {
            m_graph.addEdge(edge);
        }

        m_ui->planVacationStack->setCurrentWidget(m_ui->planVacation);
        if(m_vacationType == PlanType::DijkstraFromAnaheim)
        {
            m_ui->chooseVacationStack->setCurrentWidget(m_ui->fromAngelsStadium);
            m_ui->fromCombo->addItem("From: Angels Stadium", 62);

            for(auto stadium : Database::getStadiums())
            {
                if(stadium.getId() != 62)
                {
                    m_ui->toCombo->addItem(QString::fromStdString("To: "+stadium.getName()),stadium.getId());
                }
            }
        }
    }
}

void PlanVacationView::on_startTrip_clicked()
{
    if(m_vacationType == PlanType::DijkstraFromAnaheim)
    {
        std::map<int,std::pair<int,int>> distances;

        m_tripList.clear();
        m_distance = 0;

        m_graph.dijkstraTraversal(m_ui->fromCombo->currentData().toInt(), distances);

        bool finished = false;
        m_distance = distances[m_ui->toCombo->currentData().toInt()].first;
        int parentFrom = distances[m_ui->toCombo->currentData().toInt()].second;
        int parentTo = m_ui->toCombo->currentData().toInt();
        while (!finished)
        {
            m_tripList.push_front(parentTo);
            if (parentFrom == m_ui->fromCombo->currentData().toInt())
            {
                m_tripList.push_front(parentFrom);
                finished = true;
            }
            else
            {
                parentTo = parentFrom;
                parentFrom = distances[parentFrom].second;
            }
        }
        if(!m_tripList.empty())
        {
            m_navbar->setHidden(true);
            m_ui->planVacationStack->setCurrentWidget(m_ui->activeVacation);
            activeTrip();
        }
    }
}

void PlanVacationView::addToTrip(int id)
{
    Stadium tempStadium  = Database::findStadiumById(id);
    Team tempTeam = Database::findTeamById(tempStadium.getTeamId());

    /*  */
    auto checkIfDuplicate = [&tempStadium](const std::pair<Team,Stadium> a)
    {
        return a.second.getId() == tempStadium.getId();
    };
    auto notADuplicate = find_if(m_planList.begin(),m_planList.end(),checkIfDuplicate) == m_planList.end();

    /* If stadiumId isn't already in the list, add it to the vector and repopulate `m_stadiumListPlanner` with `m_planList` */
    if(notADuplicate)
    {
        m_planList.push_back(std::pair<Team,Stadium>(tempTeam,tempStadium));
        m_stadiumListPlanner->populateWidget(m_planList);
    }
}

void PlanVacationView::removeFromTrip(int id)
{
    Stadium tempStadium  = Database::findStadiumById(id);
    Team tempTeam = Database::findTeamById(tempStadium.getTeamId());

    /* Lamda to find matching pair of stadium id's, use std::find_if to use `checkIfExists` */
    auto checkIfExists = [&tempStadium](const std::pair<Team,Stadium> a)
    {
        return a.second.getId() == tempStadium.getId();
    };
    auto exists = std::find_if(m_planList.begin(),m_planList.end(),checkIfExists);

    // Check if iterator points to the end of the vector
    if(exists != m_planList.end())
    {
        /* If the id exsists remove from vector and if the vector is now empty clear `stadiumListPlanner`,
         *  else reload list with remaining items in the vector
         */
        m_planList.erase(exists);
        if(m_planList.empty())
            m_stadiumListPlanner->clear();
        else
            m_stadiumListPlanner->populateWidget(m_planList);
    }
}
