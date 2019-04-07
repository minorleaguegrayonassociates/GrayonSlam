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
    QListWidget::setStyleSheet("QListWidget { background-color: #303030; color: white; }");
    QListWidget::resize(parent->size());
    QListWidget::setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    QListWidget::setUniformItemSizes(true);

    /* Settings for wrapping */
    QListWidget::setWrapping(false);
    QListWidget::setFlow(QListView::TopToBottom);

    //Emits a signal when a souvenir is selected with information about the souvenir
    connect(this, &QListWidget::currentRowChanged, this, &SouvenirList::rowToIDsConverter);
}

/**
 * @brief Get IDs and its corresponding quantity
 *
 * Returns the IDs of the menu item (including the restaurant ID),
 * and the corresponding quantity that is determined by the spinbox value.
 *
 * @return IDs and its corresponding quantity
 */
const Qtys& SouvenirList::getIDQty() const
{
    return m_IDQtys;
}

/**
 * @brief Get selected IDs
 *
 * Converts the selected item into its IDs.
 *
 * @return The IDs that is selected; if nothing is selected, IDs(-1, -1) is returned.
 */
IDs SouvenirList::getSelected() const
{
    //Get the QListWidgetItem at the specified row
    QListWidgetItem* item = QListWidget::item(QListWidget::currentRow());

    //Attempt to cast the linked widget into a SouvenirListItem
    SouvenirListItem* menuItem = dynamic_cast<SouvenirListItem*>(QListWidget::itemWidget(item));

    //If successful, return the menu item's IDs
    return (menuItem != nullptr ? menuItem->getIDs()
                                : IDs(-1, -1));
}

/**
 * @brief Set IDs' quantity
 *
 * Sets the IDs' corresponding quantity to a value.
 * This is done by dynamic casting all the QListWidgetItems within the list and
 * checking if its attatched SouvenirListItem widget has the right IDs.
 *
 * @param id The IDs corresponding to a menu item
 * @param qty The value of the new quantity
 */
void SouvenirList::setQty(IDs id, int qty) const
{
    for(int i = 0; i < QListWidget::count(); i++)
    {
        QListWidgetItem* listItem = QListWidget::item(i);
        SouvenirListItem* widget = dynamic_cast<SouvenirListItem*>(QListWidget::itemWidget(listItem));

        if(widget != nullptr && id == widget->getIDs())
        {
            widget->setQty(qty);
            return;
        }
    }
}

/**
 * @brief Add menu item to the list
 *
 * Appends the given menu item to the list.
 * Any connections needed to the new item is done here.
 * If the menu item is hidden, it isn't added to the list unless SouvenirList::showHidden(true) is called.
 *
 * @param restID The restaurant ID that the menu item belongs to
 * @param menuItem The menu item to add
 */
void SouvenirList::addItem(StadiumId stadId, const Souvenir& souvenir)
{
    if(souvenir.hidden && !m_showHidden)
        return;

    QListWidgetItem* listItem = new QListWidgetItem(this);

    SouvenirListItem* widget = new SouvenirListItem(this, stadId, souvenir);
    listItem->setSizeHint(widget->getItemSizeHint());
    QListWidget::setItemWidget(listItem, widget);

    widget->showQty(m_showQty);

    //Allows all MenuItem's to toggle its quantity widgets through the emitter
    connect(this, &SouvenirList::showQtyEmitter, widget, &SouvenirListItem::showQty);

    //Handles the quantity change of a menu item
    connect(widget, &SouvenirListItem::quantityChanged, this, &SouvenirList::quantityChangedHandler);

    //Resets each spinbox of each MenuItem when emitted
    connect(this, &SouvenirList::resetQtyEmitter, widget, &SouvenirListItem::resetQty);
}

/**
 * @brief Add multiple menu items to the list
 *
 * Appends multiple menu items to the list given a restaurant.
 * Calls SouvenirList::addItem() for each menu item of the restaurant.
 *
 * @param restaurant The restaurant to add all of its items to the list
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
 * @brief Remove menu item from the list
 *
 * Removes a menu item from the list given the corresponding restaurant and menu IDs.
 * This is done by dynamic casting all the QListWidgetItems within the list and
 * checking if its attatched SouvenirListItem widget has the right IDs.
 *
 * @param id The IDs of the restaurant and the menu item to remove
 */
void SouvenirList::removeItem(IDs id)
{
    for(int i = 0; i < QListWidget::count(); i++)
    {
        QListWidgetItem* listItem = QListWidget::item(i);
        SouvenirListItem* widget = dynamic_cast<SouvenirListItem*>(QListWidget::itemWidget(listItem));

        if(widget != nullptr && id == widget->getIDs())
        {
            m_IDQtys.erase(widget->getIDs());
            QListWidget::takeItem(i);
            return;
        }
    }
}

/**
 * @brief Allow hidden menu items
 *
 * Sets whether or not hidden menu items will be added or not.
 * NOTE: Calling this function after menu items are added will have no affect on those items.
 *
 * @param v Bool value
 */
void SouvenirList::showHidden(bool v)
{
    m_showHidden = v;
}

/**
 * @brief Show the quantity spinbox
 *
 * If true, quantity spinboxes will show on each menu item.
 * This is useful if you need to input quantity for each item.
 *
 * @param v Bool value
 */
void SouvenirList::showQty(bool v)
{
    m_showQty = v;
    emit showQtyEmitter(v);
}

/**
 * @brief Reset quantities
 *
 * Clears out the container holding the IDs-quantity relationship.
 */
void SouvenirList::resetQty()
{
    m_IDQtys.clear();
    emit resetQtyEmitter();
}

/**
 * @brief Row to IDs converter
 *
 * Converts a row in the list to IDs.
 *
 * @param row The row of the item to convert
 */
void SouvenirList::rowToIDsConverter(int row) const
{
    //Get the QListWidgetItem at the specified row
    QListWidgetItem* item = QListWidget::item(row);

    //Attempt to cast the linked widget into a SouvenirListItem
    SouvenirListItem* menuItem = dynamic_cast<SouvenirListItem*>(QListWidget::itemWidget(item));

    //If successful, emit a signal
    if(menuItem != nullptr)
        emit currentSouvenirChanged(menuItem->getIDs());
}

/**
 * @brief Quantity change handler
 *
 * When a quantity spinbox has changed value, this function will store that new value.
 *
 * @param id The IDs of the changed menu item
 * @param qty The new quantity value
 */
void SouvenirList::quantityChangedHandler(IDs id, int qty)
{
    if(qty != 0)
        m_IDQtys[id] = qty; //Store/replace the key with the value
    else
        this->removeItem(id); //Erase the the key-value pair
}
