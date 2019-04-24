#include "receiptlist.hpp"
#include <QFont>

/* Static variables */
const QSize ReceiptList::receiptSizeHint(390, 50);
const double SALES_TAX = .0775;

ReceiptList::ReceiptList(QWidget* parent)
    : QListWidget(parent), m_store(data)
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

double ReceiptList::makeReciept(const IDs& souvenirData, bool grandTotal)
{
    double totalCost(0);
    double itemTotal(0);
    // All items are from the same restaurant, uses the first one to find the restaurant
    Restaurant currentRest = Database::findStadiumById(souvenirData.);
    Receipt* headerItem;
    QListWidgetItem* listItem;

    if(!grandTotal)
    {
        /* Making the QListWidgetItem that will a holdReceipt */
        listItem = new QListWidgetItem(this);
        listItem->setSizeHint(receiptSizeHint);
        listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
        QListWidget::addItem(listItem);

        /* Set the QListWidgetItem to hold a Receipt */
        headerItem = new Receipt(this, QString::fromStdString(""), Receipt::ReceiptStates::Top);
        setItemWidget(listItem, headerItem);
    }
    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    headerItem = new Receipt(this, QString::fromStdString(currentRest.GetName()), Receipt::ReceiptStates::HeaderTitle);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    headerItem = new Receipt(this, QString::fromUtf8(""), Receipt::ReceiptStates::HeaderDateTime);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    headerItem = new Receipt(this, QString::fromUtf8(""), Receipt::ReceiptStates::BodyHeader);
    setItemWidget(listItem, headerItem);

    /* iterating through each item in the menu cart and making a ReceiptBody */
    for(IDQtys::const_iterator it = menuData.begin(); it != menuData.end(); ++it)
    {
        // Get's the curren Menu item
        MenuItem currentMenuItem = currentRest.FindMenuItembyNumber(it->first.second);

        /* Making the QListWidgetItem that will hold a ReceiptBody */
        listItem = new QListWidgetItem(this);
        listItem->setSizeHint(receiptSizeHint);
        QListWidget::addItem(listItem);

        /* calculating item total qty(it->second) * price and adding it to the total bill */
        itemTotal = currentMenuItem.GetPrice()*it->second;
        totalCost += itemTotal;

        /* Set the QListWidgetItem to hold a Receipt */
        Receipt* bodyItem = new Receipt(this, it->second, currentMenuItem.GetName(), itemTotal);
        setItemWidget(listItem, bodyItem);
    }

    /* Making the QListWidgetItem that will hold a ReceiptBody for the tax total */
    listItem = new QListWidgetItem(this);
    this->setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* calculating item tax and adding it to the total cost */
    itemTotal = totalCost*SALES_TAX;
    totalCost += itemTotal;

    /* Set the QListWidgetItem to hold a Receipt */
    Receipt* bodyItem = new Receipt(this, 0, "Sales Tax", itemTotal);
    setItemWidget(listItem, bodyItem);

    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    Receipt* footerItem = new Receipt(this, QString::number(totalCost,'f',2),Receipt::ReceiptStates::FooterTotal);
    setItemWidget(listItem, footerItem);

    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    footerItem = new Receipt(this, QString::number(totalCost,'f',2),Receipt::ReceiptStates::FooterCustomerService);
    setItemWidget(listItem, footerItem);

    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    footerItem = new Receipt(this, QString::fromStdString(""),Receipt::ReceiptStates::FooterPhone);
    setItemWidget(listItem, footerItem);


    if(!grandTotal)
    {
        /* Making the QListWidgetItem that will a holdReceipt */
        listItem = new QListWidgetItem(this);
        listItem->setSizeHint(receiptSizeHint);
        QListWidget::addItem(listItem);

        /* Set the QListWidgetItem to hold a Receipt */
        headerItem = new Receipt(this, QString::fromStdString(""), Receipt::ReceiptStates::Bottom);
        setItemWidget(listItem, headerItem);
    }
    return totalCost;
}

void ReceiptList::grandTotal(vector<IDQtys> &receipts, double distance)
{
    double grandTotal(0);
    Receipt* headerItem;
    QListWidgetItem* listItem;

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    headerItem = new Receipt(this, QString::fromStdString(""), Receipt::ReceiptStates::Top);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    headerItem = new Receipt(this, QString::fromStdString(""), Receipt::ReceiptStates::GrandTotalHeader);
    setItemWidget(listItem, headerItem);

    foreach(IDQtys reciept, receipts)
    {
        grandTotal += makeReciept(reciept,true);
    }

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    headerItem = new Receipt(this, QString::number(grandTotal,'f',2), Receipt::ReceiptStates::GrandTotalFooter);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    headerItem = new Receipt(this, QString::number(distance,'f',1), Receipt::ReceiptStates::GrandTotalDistance);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    headerItem = new Receipt(this, QString::fromStdString(""), Receipt::ReceiptStates::GrandTotalThanks);
    setItemWidget(listItem, headerItem);

    /* Making the QListWidgetItem that will a holdReceipt */
    listItem = new QListWidgetItem(this);
    listItem->setSizeHint(receiptSizeHint);
    QListWidget::addItem(listItem);

    /* Set the QListWidgetItem to hold a Receipt */
    headerItem = new Receipt(this, QString::fromStdString(""), Receipt::ReceiptStates::Bottom);
    setItemWidget(listItem, headerItem);
}
