#pragma once
#include <QListWidget>
#include "souvenirlist.hpp"

class ReceiptList : public QListWidget
{
public:
    /* Constructor */
    ReceiptList(QWidget* parent);

    /* Setters */
    double makeReciept(Qtys& souvenirData, bool);
    void grandTotal(std::vector<Qtys>&, double&);
    QListWidgetItem* itemWidget();

private:
    static const QSize receiptSizeHint;
};

