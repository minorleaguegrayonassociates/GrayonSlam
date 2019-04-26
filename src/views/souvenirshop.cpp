#include "souvenirshop.hpp"
#include "ui_souvenirshop.h"
#include "src/datastore/database.hpp"

/* Constructor */
SouvenirShop::SouvenirShop(QWidget* parent)
    :View(parent), m_ui(new Ui::SouvenirShop)
{
    m_ui->setupUi(this);

    /* Active Vacation Souvenir list */
    m_vacationSouvenirList =  new SouvenirList(m_ui->activeVacationShop);
    m_vacationSouvenirList->setWrapping(false);
    m_vacationSouvenirList->setFlow(QListView::TopToBottom);

    /* Active Vacation Souvenir Cart */
    m_vacationSouvenirCart =  new SouvenirList(m_ui->activeVacationCart);
    m_vacationSouvenirCart->setWrapping(false);
    m_vacationSouvenirCart->setFlow(QListView::TopToBottom);
    m_vacationSouvenirCart->showQty(true);

    // set icon for checkout button
    m_ui->checkout->setText("\uf218");

    // ---  Demo - Delete after
    setCurrentStadiumId(50);
}

/* Destructor */
SouvenirShop::~SouvenirShop()
{
    delete m_ui;
    delete m_vacationSouvenirList;
    delete m_vacationSouvenirCart;
}

/**
 * Set's the current stadium Id and updates the ui to the new id's
 * info
 *
 * @param id - Stadium id for current stadium on the trip
 */
void SouvenirShop::setCurrentStadiumId(int id)
{
    m_currentStadiumId = id;

    resetUi();
    updateCurrentTrip();
}

/* Resets */
void SouvenirShop::resetView()
{}

void SouvenirShop::resetUi()
{
    m_vacationSouvenirList->clear();
    m_vacationSouvenirCart->clear();
}

/**
 * This function is called after `m_currentStadiumId` is set
 * and it updates `m_currentTeamId` to the teams id, updates
 * stadium souvenir list, and the header to the team name
 */
void SouvenirShop::updateCurrentTrip()
{
    // Set the TeamId to the team the user is visiting on the vacation
    m_currentTeamId = Database::findStadiumById(m_currentStadiumId).getTeamId();

    // Populate shop list with the stadiums souvenirs
    m_vacationSouvenirList->addAllItems(Database::findStadiumById(m_currentStadiumId));

    // Set header to the name of the team
    m_ui->activeVacationTeam->setText(QString::fromStdString(
                                     Database::findTeamById(m_currentTeamId).getName()));
}

/**
 * Add item from the souvenir shop to the souvenir cart
 * if the item already exists on the cart it just increments the qty
 * by 1
 */
void SouvenirShop::on_addToCart_clicked()
{
    // Will get restaurant id and menu id from currently selected menu list item
    IDs item = m_vacationSouvenirList->getSelected();

    // Get's map of items in the cart list
    Qtys cartIds(m_vacationSouvenirCart->getIDQty());

    // Will indicate if the item is in the list
    bool found = false;

    // Looks to see if the current item is already in the list - sets found to true if so
    for (Qtys::const_iterator it= cartIds.begin(); it != cartIds.end(); ++it)
    {
        if(it->first.second == item.second)
        {
            // Update Qty - increment by 1
             m_vacationSouvenirCart->setQty(it->first,it->second+1);
            found = true;
        }
    }

    /* If no item is found this will add the item to the list and sit the initial qty to 1 */
    if (!found)
    {
        /* as long as the choice isn't -1 add item to the cart */
        if(item.second != -1)
            m_vacationSouvenirCart->addItem(m_currentStadiumId,
                                            Database::findStadiumById(m_currentStadiumId).findSouvenir(item.second));
        // Set Default Qty to 1
        m_vacationSouvenirCart->setQty(item,1);
    }

}


/**
 * Removes selected item from the cart
 */
void SouvenirShop::on_removeItem_clicked()
{
    // Will get stadium id and souvenir id from currently selected souvenirListItem
    IDs item = m_vacationSouvenirCart->getSelected();

    // Removes selected item from cart
    m_vacationSouvenirCart->removeItem(item);
}
