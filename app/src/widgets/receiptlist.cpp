#include "receiptlist.hpp"
#include "src/datastore/database.hpp"
#include "src/widgets/receiptitem.hpp"
#include <QFont>
#include <QDebug>
#include <QLocale>

// Alias for ReceiptItem enum
using receiptState = ReceiptItem::ReceiptItemStates;
// Static variables
const QSize ReceiptList::receiptSizeHint(390, 50);

/* Constructor */
ReceiptList::ReceiptList(QWidget* parent)
    : QListWidget(parent)
{
    /* List widget settings */
    QListWidget::setStyleSheet("QListWidget { background-color: #303030; color: white; }");
    QListWidget::resize(QSize(420,500));
    QListWidget::setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QListWidget::setUniformItemSizes(true);
    QListWidget::setWrapping(false);
    QListWidget::setFlow(QListView::TopToBottom);
}

/**
 *  Takes a map of items purchased at one stadium, prints the receipt
 *  and returns the amount spent
 *
 * @param souvenirData - A Map of purchases made at a Stadium
 * @param grandTotal - bool indicating if this print is a grand total print
 * @return total amount spent
 */
double ReceiptList::makeReciept(Qtys& souvenirData, bool grandTotal)
{
    // All items on this receipt are from the same stadium, uses the first item to find the stadium
    Stadium currentStadium = Database::findStadiumById(souvenirData.begin()->first.first);

    /* If this is not a grand total receipt print the top */
    if(!grandTotal)
    {
        /* Set the QListWidgetItem to hold `ReceiptItem` receipt top prints  */
        QListWidgetItem* iwTop = itemWidget();
        ReceiptItem* top = new ReceiptItem(this, QString::fromStdString(""), receiptState::Top);
        QListWidget::setItemWidget(iwTop, top);
    }

    /* Set the QListWidgetItem to hold `ReceiptItem`, get team name, passes it in to print as the header. enum Header Title */
    QListWidgetItem* iwHeaderTitle = itemWidget();
    Team tempTeam = Database::findTeamById(currentStadium.getTeamId());
    ReceiptItem* headerTitle = new ReceiptItem(this, QString::fromStdString(tempTeam.getName()), receiptState::HeaderTitle);
    QListWidget::setItemWidget(iwHeaderTitle, headerTitle);

    /* Set the QListWidgetItem to hold `ReceiptItem` time and date of puchase print */
    QListWidgetItem* iwHeaderDate = itemWidget();
    ReceiptItem* headerDate = new ReceiptItem(this, QString(""), receiptState::HeaderDateTime);
    QListWidget::setItemWidget(iwHeaderDate, headerDate);

    /* Set the QListWidgetItem to hold `ReceiptItem` labels above body */
    QListWidgetItem* iwBodyHeader = itemWidget();
    ReceiptItem* bodyHeader = new ReceiptItem(this, QString(""), receiptState::BodyHeader);
    QListWidget::setItemWidget(iwBodyHeader, bodyHeader);

    double itemTotal(0);
    double totalCost(0);

    /* iterating through each item in the Souvenir cart and making a ReceiptBody */
    for(Qtys::const_iterator it = souvenirData.begin(); it != souvenirData.end(); ++it)
    {
        // Get's the curren Souvenir item
        Souvenir currentSouvenirItem = currentStadium.findSouvenir(it->first.second);

        /* calculating item total [ qty(it->second) * price ] and adding it to the total bill */
        itemTotal = currentSouvenirItem.getPrice()*it->second;
        totalCost += itemTotal;

        /* Set the QListWidgetItem to hold a regular receipt body items */
        QListWidgetItem* iwBodyItem = itemWidget();
        ReceiptItem* bodyItem = new ReceiptItem(this, it->second, currentSouvenirItem.getName(), itemTotal);
        QListWidget::setItemWidget(iwBodyItem, bodyItem);
    }

    /* Set the QListWidgetItem to hold a `ReceiptItem` footer for total */
    QListWidgetItem* iwFooterTotal = itemWidget();
    ReceiptItem* footerTotal = new ReceiptItem(this, QString::number(totalCost,'f',2),receiptState::FooterTotal);
    QListWidget::setItemWidget(iwFooterTotal, footerTotal);

    /* Set the QListWidgetItem to hold `ReceiptItem`, footer for customer service */
    QListWidgetItem* iwFooterCustService = itemWidget();
    ReceiptItem* footerCustService = new ReceiptItem(this, QString::number(totalCost,'f',2),receiptState::FooterCustomerService);
    QListWidget::setItemWidget(iwFooterCustService, footerCustService);

    /* Set the QListWidgetItem to hold a `ReceiptItem` footer phone number */
    QListWidgetItem* iwFooterPhone = itemWidget();
    ReceiptItem* footerPhone = new ReceiptItem(this, QString::fromStdString(""),receiptState::FooterPhone);
    QListWidget::setItemWidget(iwFooterPhone, footerPhone);

    /* If this isn't a grand total receipt print the receipt bottom when finished */
    if(!grandTotal)
    {
        /* Set the QListWidgetItem to hold a `ReceiptItem` receipt bottom */
        QListWidgetItem* iwReceiptBottom = itemWidget();
        ReceiptItem* receiptBottom = new ReceiptItem(this, QString::fromStdString(""), receiptState::Bottom);
        QListWidget::setItemWidget(iwReceiptBottom, receiptBottom);
    }

    return totalCost;
}

/**
 * When a vacation is concluded it prints this receipt which displays
 * all the receipts for purchases during the trip
 *
 * @param receipts - vector of souvenir items
 * @param distance - The distance traveled in the vacation
 */
void ReceiptList::grandTotal(std::vector<Qtys>& receipts, double& distance)
{
   /* Set the QListWidgetItem to hold a ReceiptItem */
    QListWidgetItem* iwGtTop= itemWidget();
    ReceiptItem* gtTop = new ReceiptItem(this, QString::fromStdString(""), receiptState::Top);
    QListWidget::setItemWidget(iwGtTop, gtTop);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    QListWidgetItem* iwGtHeader = itemWidget();
    ReceiptItem* gtHeader = new ReceiptItem(this, QString::fromStdString(""), receiptState::GrandTotalHeader);
    QListWidget::setItemWidget(iwGtHeader, gtHeader);

    // Keeps track of grand total of all the souvenir shops
    double grandTotal(0);

    for(Qtys& reciept: receipts)
        grandTotal += makeReciept(reciept,true);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    QListWidgetItem* iwGtFooter = itemWidget();
    ReceiptItem* gTFooter = new ReceiptItem(this, QString::number(grandTotal,'f',2), receiptState::GrandTotalFooter);
    QListWidget::setItemWidget(iwGtFooter, gTFooter);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    QListWidgetItem* iwGtDistance = itemWidget();
    ReceiptItem* gTDistance = new ReceiptItem(this, QLocale(QLocale::English).toString(distance), receiptState::GrandTotalDistance);
    QListWidget::setItemWidget(iwGtDistance, gTDistance);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    QListWidgetItem* iwGtThanks = itemWidget();
    ReceiptItem* gtThanks = new ReceiptItem(this, QString::fromStdString(""), receiptState::GrandTotalThanks);
    QListWidget::setItemWidget(iwGtThanks, gtThanks);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    QListWidgetItem* iwGtBottom = itemWidget();
    ReceiptItem* gtBottom = new ReceiptItem(this, QString::fromStdString(""), receiptState::Bottom);
    QListWidget::setItemWidget(iwGtBottom, gtBottom);
}

/**
 * Takes pointer to a ReceiptList adds a QListWidgetItem
 * to the list, makes it so that the user can't select the item
 * and returns a pointer to the QListWidgetItem
 *
 * @param parent - pointer to a ReceiptList
 * @return - returns a pointer to QListWidgetItem that was added to ReceiptList
*/
QListWidgetItem* ReceiptList::itemWidget()
{
    /* Make QListWidgetItem for reciept top */
    QListWidgetItem* listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
    QListWidget::addItem(listItem);
    return listItem;
}
