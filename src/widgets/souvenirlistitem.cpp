#include "souvenirlistitem.hpp"
#include "ui_souvenirlistitem.h"
#include <QDebug>

/* Constructor */
SouvenirListItem::SouvenirListItem(QWidget* parent, StadiumId stadId, const Souvenir& souvenir)
    : QWidget(parent), m_ids(stadId, souvenir.getId()), m_ui(new Ui::SouvenirListItem)
{
    m_ui->setupUi(this);

    QFont font("Font Awesome 5 Free");

    /* Name */
    font.setPixelSize(14);
    m_ui->name->setFont(font);
    m_ui->name->setWordWrap(true);
    m_ui->name->setText(QString::fromStdString(souvenir.getName()));

    /* Price */
    font.setPixelSize(12);
    m_ui->price->setFont(font);
    m_ui->price->setText("\uf155 " + QString::number(souvenir.getPrice(), 'f', 2));

    //Defaults the quantity widgets to hide
    showQty(false);

    /*
     * Converts the value change signal of the spin box
     * into a signal that emits an ID and quantity
     */
    connect(m_ui->spinBox_qty, qOverload<int>(&QSpinBox::valueChanged),
            this, &SouvenirListItem::idAndValueEmitter);
}

/* Destructor */
SouvenirListItem::~SouvenirListItem()
{
    delete m_ui;
}

/* Getters */
int SouvenirListItem::getQty() const
{
    return m_ui->spinBox_qty->value();
}

IDs SouvenirListItem::getIDs() const
{
    return m_ids;
}

/* Setters */
void SouvenirListItem::setQty(int v)
{
    m_ui->spinBox_qty->setValue(v);
}

void SouvenirListItem::setMinQty(int v)
{
    m_ui->spinBox_qty->setMinimum(v);
}

void SouvenirListItem::setMaxQty(int v)
{
    m_ui->spinBox_qty->setMaximum(v);
}

/* Public slots */
void SouvenirListItem::showQty(bool v)
{
    if(v)
    {
        m_ui->quantity->show();
        m_ui->spinBox_qty->show();
    }
    else
    {
        m_ui->quantity->hide();
        m_ui->spinBox_qty->hide();
    }
}

void SouvenirListItem::resetQty()
{
     setQty(m_ui->spinBox_qty->minimum());
}

/* Private slots */
void SouvenirListItem::idAndValueEmitter(int qty) const
{
    emit quantityChanged(m_ids, qty);
}
