#pragma once
#include <QListWidget>
#include "souvenirlistitem.hpp"

using Qtys = std::map<IDs,int>;

/**
 * @brief SouvenirList class
 *
 * Provides a simple way to list souvenirs.
 * This list isn't tied to a specific stadium, any souvenir can be added.
 *
 * To use:
 * @code{.cpp}
 * SouvenirList* list = new SouvenirList(widget);
 * list->addAllItems(stadium);
 * @endcode
 *
 * This will create a souvenir list within its parent widget.
 * Then it will add all the souvenirs of the stadium to the list.
 */
class SouvenirList : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    explicit SouvenirList(QWidget* parent);

    /* Getters */
    const Qtys& getIDQty() const;
    IDs getSelected() const;

    /* Setters */
    void setQty(IDs, int qty) const;
    void setMinQty(int);
    void setMaxQty(int);

    /* List modifiers */
    void addItem(StadiumId, const Souvenir&);
    void addAllItems(const Stadium&);
    void removeItem(IDs);

    /* Quantity */
    void showQty(bool);
    void resetQty();

    /* Hidden */
    void allowHidden(bool);

signals:
    void currentSouvenirChanged(IDs) const;
    void itemQtyChanged(IDs) const;

private slots:
    void rowToIDsEmitter(int) const;
    void quantityChangedHandler(IDs, int qty);

private:
    SouvenirListItem* castRow(int row) const;

    /* Data */
    Qtys m_IDQtys;
    int m_minQty = 0;
    int m_maxQty = 99;
    bool m_showQty = false;
    bool m_allowHidden = false;
};
