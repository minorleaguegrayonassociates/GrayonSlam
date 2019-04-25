#include "receiptitem.hpp"
#include "ui_receiptitem.h"
#include "src/datastore/database.hpp"
#include "src/widgets/receiptitem.hpp"
#include <QDateTime>

ReceiptItem::ReceiptItem(QWidget* parent, const QString& total_restName, const ReceiptItemStates& thisTemplate)
    : QWidget(parent), m_ui(new Ui::ReceiptItem)
{
    m_ui->setupUi(this);
    m_defaultFontSyle.setFamily("IBM Plex Mono");

    switch(thisTemplate)
    {
    case ReceiptItemStates::GrandTotalHeader:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalHeader);
        m_ui->GrandTotalHeaderLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::GrandTotalFooter:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalFooter);
        m_ui->GrandTotalFooterLabel->setFont(m_defaultFontSyle);
        m_ui->GrandTotalFooterLabel_2->setText("$"+total_restName);
        m_ui->GrandTotalFooterLabel_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::GrandTotalThanks:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalThanks);
        m_ui->GrandTotalThanksLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::GrandTotalDistance:
        m_ui->receiptStack->setCurrentWidget(m_ui->grandTotalDistance);
        m_ui->GrandTotalDistanceLabel_2->setText(total_restName+" mi.");
        m_ui->GrandTotalDistanceLabel->setFont(m_defaultFontSyle);
        m_ui->GrandTotalDistanceLabel_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::HeaderTitle:
        m_ui->receiptStack->setCurrentWidget(m_ui->headerTitle);
        m_ui->restaurantName->setText(total_restName);
        m_ui->restaurantName->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::HeaderDateTime:
        m_ui->receiptStack->setCurrentWidget(m_ui->headerDateTime);
        m_ui->date->setText(QDate::currentDate().toString());
        m_ui->date->setFont(m_defaultFontSyle);
        m_ui->time->setText(QTime::currentTime().toString());
        m_ui->time->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::FooterTotal:
        m_ui->receiptStack->setCurrentWidget(m_ui->footerTotal);
        m_ui->total->setText("$"+total_restName);
        m_ui->total->setFont(m_defaultFontSyle);
        m_ui->totalLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::FooterCustomerService:
        m_ui->receiptStack->setCurrentWidget(m_ui->footerCustomerService);
        m_ui->customerServiceLabel->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::FooterPhone:
        m_ui->receiptStack->setCurrentWidget(m_ui->footerPhone);
        m_ui->customerServiceLabel_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::BodyHeader:
        m_ui->receiptStack->setCurrentWidget(m_ui->bodyHeader);
        m_ui->qty_2->setFont(m_defaultFontSyle);
        m_ui->item_2->setFont(m_defaultFontSyle);
        m_ui->price_2->setFont(m_defaultFontSyle);
        break;
    case ReceiptItemStates::Body:
        // Use the other constructor
        break;
    case ReceiptItemStates::Top:
        m_ui->receiptStack->setCurrentWidget(m_ui->top);
        break;
    case ReceiptItemStates::Bottom:
        m_ui->receiptStack->setCurrentWidget(m_ui->bottom);
        break;
    }
}

ReceiptItem::ReceiptItem(QWidget* parent, const int& qty, const std::string& itemName, const double& price) :
    QWidget(parent),
    m_ui(new Ui::ReceiptItem)
{
    m_ui->setupUi(this);

    // Set font to IBM Plex Mono
    m_defaultFontSyle.setFamily("IBM Plex Mono");

    // Flip stack widget to "body" page
    m_ui->receiptStack->setCurrentWidget(m_ui->body);

    /* set label fields */
    m_ui->qty->setText(QString::number(qty));
    m_ui->item->setText(QString::fromStdString(itemName));
    m_ui->price->setText("$"+QString::number(price,'f',2));

    /* Set font */
    m_ui->qty_2->setFont(m_defaultFontSyle);
    m_ui->item_2->setFont(m_defaultFontSyle);
    m_ui->price_2->setFont(m_defaultFontSyle);

    // Sales tax doesn't need qty, if 0 hide qty
    if(qty == 0)
    {
        m_ui->qty->setHidden(true);
        m_ui->item->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

ReceiptItem::~ReceiptItem()
{
    delete m_ui;
}
