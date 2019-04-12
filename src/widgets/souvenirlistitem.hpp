#pragma once
#include <QWidget>
#include "src/datastore/stadium.hpp"

using StadiumId = int;
using SouvenirId = int;
using IDs = std::pair<StadiumId,SouvenirId>;

namespace Ui
{
class SouvenirListItem;
}

class SouvenirListItem : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit SouvenirListItem(QWidget* parent, StadiumId, const Souvenir&);

    /* Destructor */
    ~SouvenirListItem() override;

    /* Getters */
    int getQty() const;
    IDs getIDs() const;

    /* Setters */
    void setQty(int);
    void setMinQty(int);
    void setMaxQty(int);

public slots:
    void showQty(bool);
    void resetQty();

signals:
    void quantityChanged(IDs, int qty) const;

private slots:
    void idAndValueEmitter(int) const;

private:
    IDs m_ids;
    Ui::SouvenirListItem* m_ui;
};
