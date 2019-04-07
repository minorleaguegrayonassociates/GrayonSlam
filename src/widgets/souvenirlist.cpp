#include "souvenirlist.hpp"

/**
 * Constructs a menu list within the given parent widget. All default
 * settings are set when created.
 *
 * @param parent Widget to display the list in
 */
SouvenirList::SouvenirList(QWidget* parent)
    : QListWidget(parent)
{
    /* List widget settings */
    QListWidget::resize(parent->size());
    QListWidget::setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QListWidget::setUniformItemSizes(true);

    /* Settings for wrapping */
    QListWidget::setWrapping(false);
    QListWidget::setFlow(QListView::TopToBottom);

    //Emits a signal when a souvenir is selected with information about the souvenir
    connect(this, &QListWidget::currentRowChanged, this, &SouvenirList::rowToIDsEmitter);
}

/**
 * Returns a map of stadium ID and souvenir ID pairs and their
 * corresponding quantity that is determined by the spinbox value.
 *
 * @return Map containing the IDs and quantities
 */
const Qtys& SouvenirList::getIDQty() const
{
    return m_IDQtys;
}

/**
 * Attempts to convert the currently selected item into a
 * SouvenirListItem. If successful, the IDs of the item is
 * returned; otherwise, return invalid IDs.
 *
 * @return IDs of the selected item. If nothing is selected, @a IDs(-1,-1) is returned.
 */
IDs SouvenirList::getSelected() const
{
    SouvenirListItem* widget = castRow(QListWidget::currentRow());

    return (widget != nullptr ? widget->getIDs()
                              : IDs(-1, -1));
}

/**
 * @brief Set a specific souvenir's quantity
 *
 * Sets the IDs' corresponding quantity to a value. This is done by
 * casting each widget into a @a SouvenirListItem and checking if
 * it has the matching IDs.
 *
 * @param id IDs corresponding to a menu item
 * @param qty Value of the new quantity
 */
void SouvenirList::setQty(IDs id, int qty) const
{
    for(int row = 0; row < QListWidget::count(); row++)
    {
        SouvenirListItem* widget = castRow(row);

        if(widget != nullptr && id == widget->getIDs())
        {
            widget->setQty(qty);
            return;
        }
    }
}

/**
 * Sets the minimum quantity that an item's spinbox can have.
 * This is done by going through each item and setting its
 * attached widget's minumum quantity.
 *
 * NOTE:
 * When the minimum quantity is the value of the spinbox, the
 * item is removed from the list. If you want a minimum value
 * of 0, call this function with a value of -1.
 *
 * @param qty Minimum quantity
 */
void SouvenirList::setMinQty(int qty)
{
    m_minQty = qty;

    for(int row = 0; row < QListWidget::count(); row++)
    {
        SouvenirListItem* widget = castRow(row);

        if(widget != nullptr) { widget->setMinQty(qty); };
    }
}

/**
 * Sets the maximum quantity that an item's spinbox can have.
 * This is done by going through each item and setting its
 * attached widget's maximum quantity.
 *
 * @param qty Maximum quantity
 */
void SouvenirList::setMaxQty(int qty)
{
    m_maxQty = qty;

    for(int row = 0; row < QListWidget::count(); row++)
    {
        SouvenirListItem* widget = castRow(row);

        if(widget != nullptr) { widget->setMaxQty(qty); };
    }
}

/**
 * @brief Add a souvenir to the list
 *
 * Creates a new widget and item and attaches them together.
 * The new item is added to the list with the appropriate size.
 * Then, the widget's quantity changed signal is connected
 * to the list's handler.
 *
 * @param stadId Stadium ID that the souvenir belongs to
 * @param souvenir Souvenir to add
 */
void SouvenirList::addItem(StadiumId stadId, const Souvenir& souvenir)
{
    if(souvenir.hidden && !m_allowHidden)
        return;

    SouvenirListItem* widget = new SouvenirListItem(this, stadId, souvenir);

    //Handles the quantity change of the widget
    connect(widget, &SouvenirListItem::quantityChanged,
            this, &SouvenirList::quantityChangedHandler);

    /* Change the settings of the widget */
    widget->showQty(m_showQty);
    widget->setMinQty(m_minQty);
    widget->setMaxQty(m_maxQty);
    widget->setQty(m_minQty + 1); //Triggers widget's quantityChanged()

    //Add a new item to the list
    QListWidgetItem* item = new QListWidgetItem(this);
    item->setSizeHint(widget->size());

    //Attach the widget to the item
    QListWidget::setItemWidget(item, widget);
}

/**
 * @brief Add all of a stadium's souvenirs to the list
 *
 * Clears the current list and calls @a addItem() on each of
 * the souvenirs in the stadium.
 *
 * @param stadium Stadium that holds the souvenirs
 */
void SouvenirList::addAllItems(const Stadium& stadium)
{
    QListWidget::clear();

    for(const Souvenir& souvenir : stadium.getSouvenirs())
    {
        addItem(stadium.getId(), souvenir);
    }
}

/**
 * @brief Remove souvenir from the list
 *
 * Searches through the list and looks for matching IDs by casting
 * each widget into a @a SouvenirListItem. When found, the souvenir
 * is removed from the IDs-quantity map as well as the list.
 *
 * @param id IDs of the souvenir to remove
 */
void SouvenirList::removeItem(IDs id)
{
    for(int row = 0; row < QListWidget::count(); row++)
    {
        SouvenirListItem* widget = castRow(row);

        if(widget != nullptr && id == widget->getIDs())
        {
            m_IDQtys.erase(widget->getIDs());
            QListWidget::takeItem(row);
            return;
        }
    }
}

/**
 * Each item's quantity spinbox will either hide or show depending
 * on @a show. This is useful if you need to input quantity for each item.
 *
 * @param show Show each item's quantity spinbox
 */
void SouvenirList::showQty(bool show)
{
    m_showQty = show;

    for(int row = 0; row < QListWidget::count(); row++)
    {
        SouvenirListItem* widget = castRow(row);

        if(widget != nullptr) { widget->showQty(show); }
    }
}

/**
 * Clears out the container holding the IDs-quantity relationship
 * and changes resets each widget's quantity.
 */
void SouvenirList::resetQty()
{
    m_IDQtys.clear();

    for(int row = 0; row < QListWidget::count(); row++)
    {
        SouvenirListItem* widget = castRow(row);

        if(widget != nullptr) { widget->resetQty(); }
    }
}

/**
 * Sets whether or not hidden souvenirs will be added or not.
 *
 * NOTE:
 * Calling this function after items are added will have
 * no affect on those items.
 *
 * @param allow Allow hidden souvenirs to show
 */
void SouvenirList::allowHidden(bool allow)
{
    m_allowHidden = allow;
}

/**
 * Converts a row in the list to IDs and emits a signal with those IDs.
 *
 * @param row Row of the item to convert into IDs
 */
void SouvenirList::rowToIDsEmitter(int row) const
{
    SouvenirListItem* widget = castRow(row);

    if(widget != nullptr)
    {
        emit currentSouvenirChanged(widget->getIDs());
    }
}

/**
 * When a quantity spinbox has changed value, this function will
 * store that new value. If the changing quantity is the minimum
 * quantity, the changed item is removed from the list.
 *
 * @param id IDs of the changed souvenir
 * @param qty New quantity value
 */
void SouvenirList::quantityChangedHandler(IDs id, int qty)
{
    if(qty != m_minQty)
    {
        m_IDQtys[id] = qty; //Store/replace the key with the value
    }
    else
    {
        removeItem(id); //Remove it from the list
    }
}

/**
 * Dynamic casts a QListWidgetItem at a given row in the list; the
 * result is returned.
 *
 * @param row Row of an item in the list
 * @return Pointer to a SouvenirListItem
 */
SouvenirListItem* SouvenirList::castRow(int row) const
{
    QListWidgetItem* item = QListWidget::item(row);
    return dynamic_cast<SouvenirListItem*>(QListWidget::itemWidget(item));
}
