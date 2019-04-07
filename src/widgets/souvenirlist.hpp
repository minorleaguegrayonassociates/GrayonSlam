#pragma once
#include <QListWidget>
#include "src/widgets/souvenirlistitem.hpp"

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

    /* List modifiers */
    void addItem(StadiumId, const Souvenir&);
    void addAllItems(const Stadium&);
    void removeItem(IDs);
    void showHidden(bool);

    /* Quantity */
    void showQty(bool);
    void resetQty();

signals:
    void currentSouvenirChanged(IDs) const;
    void showQtyEmitter(bool) const;
    void resetQtyEmitter() const;

private slots:
    void rowToIDsConverter(int row) const;
    void quantityChangedHandler(IDs, int qty);

private:
    Qtys m_IDQtys;
    bool m_showQty = false;
    bool m_showHidden = false;
};
