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

    m_souvenirShop = new SouvenirShop(m_ui->activeVacation);
    m_receiptViews = new ReceiptView(m_ui->vacationReceipt);
    m_mapView = new MapView(m_ui->tripMap);

    m_tripList.push_back(50);
    m_tripList.push_back(51);
    m_tripList.push_back(52);
    m_tripList.push_back(53);
    m_tripList.push_back(54);

    connect(m_souvenirShop,SIGNAL(goToReceipt(Qtys&)), this, SLOT(setReceipt(Qtys&)));
    connect(m_souvenirShop,&SouvenirShop::skipCheckout,this,&PlanVacationView::goToNext);
    connect(m_receiptViews,&ReceiptView::goToNext,this,&PlanVacationView::goToNext);
    connect(m_mapView,&MapView::goToShop,this,&PlanVacationView::goToShop);
    connect(m_ui->ContinueToNext,&QAbstractButton::clicked,this,&PlanVacationView::resetUi);
    activeTrip();
}

/* Destructor */
PlanVacationView::~PlanVacationView()
{
    delete m_ui;
    delete m_souvenirShop;
    delete m_receiptViews;
    delete m_mapView;
}

/* Resets */
void PlanVacationView::resetView()
{
    m_ui->planVacationStack->setCurrentWidget(m_ui->activeVacation);
}

void PlanVacationView::resetUi()
{
    m_navbar->setHidden(false);
    m_previousStadiumId = -1;
    m_currentStadiumId = -1;
    m_ui->planVacationStack->setCurrentWidget(m_ui->chooseType);
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
    if(m_previousStadiumId == -1)
    {
        m_navbar->setHidden(true);
    }
    // Store previous Id then removing it from the `tripList`
    m_previousStadiumId  = m_tripList.front();

    /* If the `tripList` isn't already empty, erase the last stadium */
    if(!m_tripList.empty())
        m_tripList.pop_front();

    // Continue with the trip
    PlanVacationView::activeTrip();
}

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

        /* If the value of `m_previousStadiumId` has been set then turn stack to `tripMap` and set animation */
        if(m_previousStadiumId != -1)
        {
            m_ui->planVacationStack->setCurrentWidget(m_ui->tripMap);
            m_mapView->setAnimation(m_previousStadiumId,m_currentStadiumId);
        }
    }
    else if(!m_receiptVector.empty())
    {
        m_printedGrandTotal = true;
        m_ui->planVacationStack->setCurrentWidget(m_ui->vacationReceipt);
        m_receiptViews->grandTotal(m_receiptVector, 0.0);
        m_receiptVector.clear();
    }
    else if(!m_printedGrandTotal)
    {
        m_ui->planVacationStack->setCurrentWidget(m_ui->vacationDistance);
        m_ui->distance->setText(QString::fromStdString("0.0 miles"));
    }
    else
    {
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
