#include "receiptlist.hpp"
#include "src/datastore/database.hpp"
#include "src/widgets/receiptitem.hpp"
#include <QFont>

/* Static variables */
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

    /* Settings for wrapping */
    QListWidget::setWrapping(false);
    QListWidget::setFlow(QListView::TopToBottom);

}

double ReceiptList::makeReciept(Qtys& souvenirData, bool grandTotal)
{
    double totalCost(0);
    double itemTotal(0);

    // All items are from the same stadium, uses the first one to find the stadium
    Stadium currentStadium = Database::findStadiumById(souvenirData.begin()->first.first);

    ReceiptItem* headerItem;
    QListWidgetItem* listItem;

    if(!grandTotal)
    {
        /* Making the QListWidgetItem that will a holdReceiptItem */
        listItem = new QListWidgetItem(this);
        listItem->setSizeHint(receiptSizeHint);
        listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
        QListWidget::addItem(listItem);

        /* Set the QListWidgetItem to hold a ReceiptItem */
        headerItem = new ReceiptItem(this, QString::fromStdString(""), ReceiptItem::ReceiptItemStates::Top);
        setItemWidget(listItem, headerItem);
    }
    /* Making the QListWidgetItem that will a holdReceiptItem */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(currentStadium.getName()), ReceiptItem::ReceiptItemStates::HeaderTitle);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceiptItem */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    headerItem = new ReceiptItem(this, QString::fromUtf8(""), ReceiptItem::ReceiptItemStates::HeaderDateTime);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceiptItem */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    headerItem = new ReceiptItem(this, QString::fromUtf8(""), ReceiptItem::ReceiptItemStates::BodyHeader);
    setItemWidget(listItem, headerItem);

    /* iterating through each item in the Souvenir cart and making a ReceiptBody */
    for(Qtys::const_iterator it = souvenirData.begin(); it != souvenirData.end(); ++it)
    {
        // Get's the curren Souvenir item
        Souvenir currentSouvenirItem = currentStadium.findSouvenir(it->first.second);

        /* Making the QListWidgetItem that will hold a ReceiptBody */
        listItem = new QListWidgetItem(this);
        listItem->setSizeHint(receiptSizeHint);
        QListWidget::addItem(listItem);

        /* calculating item total qty(it->second) * price and adding it to the total bill */
        itemTotal = currentSouvenirItem.getPrice()*it->second;
        totalCost += itemTotal;

        /* Set the QListWidgetItem to hold a ReceiptItem */
        ReceiptItem* bodyItem = new ReceiptItem(this, it->second, currentSouvenirItem.getName(), itemTotal);
        setItemWidget(listItem, bodyItem);
    }

    /* Making the QListWidgetItem that will hold a ReceiptBody for the tax total */
    listItem = new QListWidgetItem(this);
    this->setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* calculating item tax and adding it to the total cost */
    itemTotal = totalCost;
    totalCost += itemTotal;

    /* Set the QListWidgetItem to hold a ReceiptItem */
    ReceiptItem* bodyItem = new ReceiptItem(this, 0, "Sales Tax", itemTotal);
    setItemWidget(listItem, bodyItem);

    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    ReceiptItem* footerItem = new ReceiptItem(this, QString::number(totalCost,'f',2),ReceiptItem::ReceiptItemStates::FooterTotal);
    setItemWidget(listItem, footerItem);

    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    footerItem = new ReceiptItem(this, QString::number(totalCost,'f',2),ReceiptItem::ReceiptItemStates::FooterCustomerService);
    setItemWidget(listItem, footerItem);

    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    footerItem = new ReceiptItem(this, QString::fromStdString(""),ReceiptItem::ReceiptItemStates::FooterPhone);
    setItemWidget(listItem, footerItem);


    if(!grandTotal)
    {
        /* Making the QListWidgetItem that will a holdReceipt */
        listItem = new QListWidgetItem(this);
        listItem->setSizeHint(receiptSizeHint);
        QListWidget::addItem(listItem);

        /* Set the QListWidgetItem to hold a ReceiptItem */
        headerItem = new ReceiptItem(this, QString::fromStdString(""), ReceiptItem::ReceiptItemStates::Bottom);
        setItemWidget(listItem, headerItem);
    }
    return totalCost;
}

void ReceiptList::grandTotal(std::vector<Qtys>& receipts, double& distance)
{
    double grandTotal(0);
    ReceiptItem* headerItem;
    QListWidgetItem* listItem;

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), ReceiptItem::ReceiptItemStates::Top);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), ReceiptItem::ReceiptItemStates::GrandTotalHeader);
    setItemWidget(listItem, headerItem);

    for(Qtys& reciept: receipts)
        grandTotal += makeReciept(reciept,true);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::number(grandTotal,'f',2), ReceiptItem::ReceiptItemStates::GrandTotalFooter);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::number(distance,'f',1), ReceiptItem::ReceiptItemStates::GrandTotalDistance);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), ReceiptItem::ReceiptItemStates::GrandTotalThanks);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a ReceiptItem */
    headerItem = new ReceiptItem(this, QString::fromStdString(""), ReceiptItem::ReceiptItemStates::Bottom);
    setItemWidget(listItem, headerItem);
}
