#include "receiptlist.hpp"
#include "src/datastore/database.hpp"
#include "src/widgets/receiptitem.hpp"
#include <QFont>

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
    QListWidget::resize(parent->size());
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
        ReceiptItem top(this, QString::fromStdString(""), receiptState::Top);
        setItemWidget(itemWidget(this), &top);
    }

    /* Set the QListWidgetItem to hold `ReceiptItem`, team name prints as the header. enum Header Title */
    ReceiptItem* headerTitle = new ReceiptItem(this, QString::fromStdString(currentStadium.getName()), receiptState::HeaderTitle);
    setItemWidget(itemWidget(this), headerTitle);

    /* Set the QListWidgetItem to hold `ReceiptItem` time and date of puchase print */
    ReceiptItem* headerDate = new ReceiptItem(this, QString::fromStdString(""), receiptState::HeaderDateTime);
    setItemWidget(itemWidget(this), headerDate);

    /* Set the QListWidgetItem to hold `ReceiptItem` labels above body */
    ReceiptItem* bodyHeader = new ReceiptItem(this, QString::fromStdString(""), receiptState::BodyHeader);
    setItemWidget(itemWidget(this), bodyHeader);

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
        ReceiptItem* bodyItem = new ReceiptItem(this, it->second, currentSouvenirItem.getName(), itemTotal);
        setItemWidget(itemWidget(this), bodyItem);
    }

    /* calculating item tax and adding it to the total cost */
    itemTotal = totalCost;
    totalCost += itemTotal;

    /* Set the QListWidgetItem to hold a `ReceiptItem` footer for total */
    ReceiptItem* footerTotal = new ReceiptItem(this, QString::number(totalCost,'f',2),receiptState::FooterTotal);
    setItemWidget(itemWidget(this), footerTotal);

    /* Set the QListWidgetItem to hold `ReceiptItem`, footer for customer service */
    ReceiptItem* footerCustService = new ReceiptItem(this, QString::number(totalCost,'f',2),receiptState::FooterCustomerService);
    setItemWidget(itemWidget(this), footerCustService);

    /* Set the QListWidgetItem to hold a `ReceiptItem` footer phone number */
    ReceiptItem* footerPhone = new ReceiptItem(this, QString::fromStdString(""),receiptState::FooterPhone);
    setItemWidget(itemWidget(this), footerPhone);

    /* If this isn't a grand total receipt print the receipt bottom when finished */
    if(!grandTotal)
    {
        /* Set the QListWidgetItem to hold a `ReceiptItem` receipt bottom */
        ReceiptItem* receiptBottom = new ReceiptItem(this, QString::fromStdString(""), receiptState::Bottom);
        setItemWidget(itemWidget(this), receiptBottom);
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
    double grandTotal(0);
    ReceiptItem* headerItem;

   /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), receiptState::Top);
    setItemWidget(itemWidget(this), headerItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), receiptState::GrandTotalHeader);
    setItemWidget(itemWidget(this), headerItem);

    for(Qtys& reciept: receipts)
        grandTotal += makeReciept(reciept,true);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::number(grandTotal,'f',2), receiptState::GrandTotalFooter);
    setItemWidget(itemWidget(this), headerItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::number(distance,'f',1), receiptState::GrandTotalDistance);
    setItemWidget(itemWidget(this), headerItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), receiptState::GrandTotalThanks);
    setItemWidget(itemWidget(this), headerItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), receiptState::Bottom);
    setItemWidget(itemWidget(this), headerItem);
}

/**
 * Takes pointer to a ReceiptList adds a QListWidgetItem
 * to the list, makes it so that the user can't select the items
 * and returns a pointer to the QListWidgetItem
 *
 * @param parent - pointer to a ReceiptList
 * @return - returns a pointer to QListWidgetItem that was added to ReceiptList
*/
QListWidgetItem* ReceiptList::itemWidget(ReceiptList* parent)
{
    /* Make QListWidgetItem for reciept top */
    QListWidgetItem* listItem = new QListWidgetItem(parent);
    listItem->setSizeHint(receiptSizeHint);
    listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
    QListWidget::addItem(listItem);
    return listItem;
}
