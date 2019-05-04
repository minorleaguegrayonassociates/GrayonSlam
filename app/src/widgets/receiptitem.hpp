#pragma once
#include <QWidget>

namespace Ui {
class ReceiptItem;
}

class ReceiptItem : public QWidget
{
    Q_OBJECT
public:
    /* Enum class for each receipt state */
    enum class ReceiptItemStates { GrandTotalHeader, GrandTotalFooter, GrandTotalThanks,
                                   GrandTotalDistance, HeaderTitle, HeaderDateTime,
                                   FooterTotal, FooterCustomerService, FooterPhone,
                                   BodyHeader, Body, Top, Bottom};
    /* Constructors */
    ReceiptItem(QWidget* parent, const QString& total_restName, const ReceiptItemStates&);
    ReceiptItem(QWidget* parent, const int& qty, const std::string& itemName, const double& price);

    /* Destructors */
    ~ReceiptItem();

private:
    Ui::ReceiptItem* m_ui;
    ReceiptItemStates m_state;
    QFont m_defaultFontSyle;
};

