#include "planvacationview.hpp"
#include "ui_planvacationview.h"
#include "src/datastore/database.hpp"

/* Constructor */
PlanVacationView::PlanVacationView(QWidget *parent, NavBar* bar)
    : View(parent), m_ui(new Ui::PlanVacationView), m_navbar(bar),
      m_previousStadiumId(-1), m_currentStadiumId(-1)
{
    m_ui->setupUi(this);

    m_souvenirShop = new SouvenirShop(m_ui->activeVacation);
    m_receiptViews = new ReceiptView(m_ui->vacationReceipt);

    m_tripList.push_back(50);
    m_tripList.push_back(51);
    m_tripList.push_back(52);
    m_tripList.push_back(53);
    m_tripList.push_back(54);

    connect(m_souvenirShop,SIGNAL(goToReceipt(Qtys&)), this, SLOT(setReceipt(Qtys&)));
    connect(m_souvenirShop,&SouvenirShop::goToNext,this,&PlanVacationView::goToNext);
    connect(m_receiptViews,&ReceiptView::goToNext,this,&PlanVacationView::goToNext);

    activeTrip();
}

/* Destructor */
PlanVacationView::~PlanVacationView()
{
    delete m_ui;
    delete m_navbar;
    delete m_souvenirShop;
    delete m_receiptViews;
}

/* Resets */
void PlanVacationView::resetView()
{}

void PlanVacationView::resetUi()
{
    m_navbar->setHidden(false);
    m_receiptVector.clear();
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
    // Store previous Id then removing it from the `tripList`
    m_previousStadiumId  = m_tripList.front();
    m_tripList.pop_front();

    if(!m_tripList.empty())
    {
        PlanVacationView::activeTrip();
    }
    else
    {
        PlanVacationView::resetUi();
    }
}

void PlanVacationView::activeTrip()
{
    /* If the `tripList` isn't empty go to the next stadium, otherwise, if the receiptVector isn't empty
     * print out the grandTotal receipt for all the items bought at each stadium, if the user didn't purchase
     * anything call `resetUi`
     */
    if(!m_tripList.empty())
    {
        // Switch `planVacationStack` page to `activeVacation`
        m_ui->planVacationStack->setCurrentWidget(m_ui->activeVacation);

        /* Set current id, then set `souvenirShop` to the `m_currentStadiumId` */
        m_currentStadiumId = m_tripList.front();
        m_souvenirShop->setCurrentStadiumId(m_currentStadiumId);
    }
    else if(m_receiptVector.size() != 0)
    {
        m_ui->planVacationStack->setCurrentWidget(m_ui->vacationReceipt);
        m_receiptViews->grandTotal(m_receiptVector, 0.0);
    }
    else
    {
        PlanVacationView::resetUi();
    }
}
