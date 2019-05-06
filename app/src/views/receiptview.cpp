#include "receiptview.hpp"
#include "ui_receiptview.h"

/* Constructor */
ReceiptView::ReceiptView(QWidget* parent)
    :View(parent), m_ui(new Ui::ReceiptView)
{
    m_ui->setupUi(this);
    m_receipt = new ReceiptList(m_ui->ReceiptWidget);

    connect(m_receipt,&QListWidget::itemChanged,this,[&](){
        if(m_receipt->count() >= 10)
        {
            m_receipt->resize(410,500);
        }
        else
        {
            m_receipt->resize(400,500);
        }
    });
}

/* Destructor */
ReceiptView::~ReceiptView()
{
    delete m_ui;
    delete m_receipt;
}

/* Reset Functions */
void ReceiptView::resetView()
{}

void ReceiptView::resetUi()
{}

/**
 * When this function is called it clears the `ReceiptList`
 * and make a new receipt with the information passed in
 *
 * @param receipt - Map of Stadium,Team and souvenir id's - used to print receipt
 * @param isGrandTotal - bool that indicates whether or not to print top/bottom of the receipt
 */
void ReceiptView::makeReceipt(Qtys& receipt,bool isGrandTotal)
{
    m_receipt->clear();
    m_receipt->makeReciept(receipt, isGrandTotal);
}

/**
 * When this function is called it clears the `ReceiptList`
 * and make a all the receipts within the vector as one grand total receipt
 *
 * @param receipts - vector of receipt data to print all of the receipts for the trip
 * @param distance - total distance traveled will be printed at the bottom of the receipt
 */
void ReceiptView::grandTotal(std::vector<Qtys>& receipts,double distance)
{
    m_receipt->clear();
    m_receipt->grandTotal(receipts,distance);
}

/**
 * Sends a public signal when QPushButton `continueToNext`
 * is clicked
 */
void ReceiptView::on_continueToNext_clicked()
{
   emit goToNext();
}
