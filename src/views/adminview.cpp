#include "adminview.hpp"
#include "ui_adminview.h"
#include "src/datastore/database.hpp"

AdminView::AdminView(QWidget* parent)
    : View(parent), m_ui(new Ui::AdminView)
{
    m_ui->setupUi(this);

    /* Initialize souvenir lists */
    m_availableSouvenirList = new SouvenirList(m_ui->widget_souvAvailableList);
    m_hiddenSouvenirList = new SouvenirList(m_ui->widget_souvHiddenList);
    m_hiddenSouvenirList->allowHidden(true);
}

/**
 * Deletes all the widgets in the view.
 */
AdminView::~AdminView()
{
    delete m_ui;
    delete m_availableSouvenirList;
    delete m_hiddenSouvenirList;
}

/**
 * Resets the stacked widget page and UI by calling @a resetUi().
 */
void AdminView::resetView()
{
    //Change to stadium list page
    m_ui->stackedWidget->setCurrentIndex(0);

    m_currentStadiumId = -1;

    resetUi();
}

/**
 * Resets the UI to their original state.
 */
void AdminView::resetUi()
{
    loadSouvenirLists(m_currentStadiumId);
}

/**
 * @brief Clear and load souvenir lists
 *
 * A stadium object is extracted from the database using @a stadiumId.
 * The souvenirs of the extracted stadium is used to fill the
 * available and hidden souvenir lists. As a precaution, the lists
 * are cleared to remove any leftover items in the lists.
 *
 * If the passed ID results in an invalid stadium, this function does nothing.
 *
 * @param stadiumId Stadium ID with souvenirs to use in the lists
 */
void AdminView::loadSouvenirLists(int stadiumId)
{
    /* Extract stadium from database and check if valid */
    const Stadium& stadium = Database::findStadiumById(stadiumId);
    if(stadium.getId() == -1)
        return;

    /* Clear current lists */
    m_availableSouvenirList->clear();
    m_hiddenSouvenirList->clear();

    /* Get the stadium and add each souvenir into the lists */
    for(const Souvenir& souvenir : stadium.getSouvenirs())
    {
        if(souvenir.hidden)
            m_hiddenSouvenirList->addItem(stadium.getId(), souvenir);
        else
            m_availableSouvenirList->addItem(stadium.getId(), souvenir);
    }
}

/**
 * @brief Fill stadium edit fields
 *
 *
 *
 * @param stadiumId Stadium ID to fill the edit fields with
 */
void AdminView::fillStadiumEditFields(int stadiumId)
{
    /* Extract stadium from database and check if valid */
    const Stadium& stadium = Database::findStadiumById(stadiumId);
//    const Team& team = Database::findTeamById(stadiumId.getTeamId());
    if(stadium.getId() == -1)
        return;

    m_ui->lineEdit_stadName->setText(QString::fromStdString(stadium.getName()));
    m_ui->lineEdit_stadLocation->setText(QString::fromStdString(stadium.getLocation()));
    m_ui->lineEdit_stadTeamName->setText("wuhoh");
    m_ui->comboBox_stadLeague->
}

/**
 * Goes back to stadium list page by calling @a resetView().
 */
void AdminView::on_pushButton_souvGoBack_clicked()
{
    resetView();
}
