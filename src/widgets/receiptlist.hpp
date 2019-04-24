#pragma once

#include <QObject>
#include <QListWidget>
#include <QListWidgetItem>
#include "souvenirlist.hpp"
#include "src/datastore/database.hpp"
#include "src/widgets/receiptlist.hpp"

class ReceiptList : public QListWidget
{
public:
    ReceiptList(QWidget* parent);
    double makeReciept(const IDs& souvenirData, bool = false);
    void grandTotal(std::vector<IDs>&, double);
private:
    static const QSize receiptSizeHint;
};

