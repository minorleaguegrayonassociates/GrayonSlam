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

    connect(m_ui->spinBox, qOverload<int>(&QSpinBox::valueChanged), this, &AdminView::fillStadiumEditFields);

    connect(m_availableSouvenirList, &SouvenirList::currentSouvenirChanged,
            [&](IDs ids)
            {
                //Deselect current selection on hidden souvenir list
                m_hiddenSouvenirList->setCurrentRow(-1);

                fillSouvenirEditFields(ids.second);
            });

    connect(m_hiddenSouvenirList, &SouvenirList::currentSouvenirChanged,
            [&](IDs ids)
            {
                //Deselect current selection on hidden souvenir list
                m_availableSouvenirList->setCurrentRow(-1);

                fillSouvenirEditFields(ids.second);
            });
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
 * Fills all the stadium edit fields with information about a stadium
 * that is represented by @a stadiumId.
 *
 * If @a stadiumId doesn't represent an existing stadium, this
 * function does nothing.
 *
 * @param stadiumId Stadium ID to fill the edit fields with
 */
void AdminView::fillStadiumEditFields(int stadiumId)
{
    /* Extract stadium from database and check if valid */
    const Stadium& stadium = Database::findStadiumById(stadiumId);
    if(stadium.getId() == -1)
        return;

    //Extract the team that lives in the stadium
    const Team& team = Database::findTeamById(stadium.getTeamId());

    /* Fill line edits */
    m_ui->lineEdit_stadName->setText(QString::fromStdString(stadium.getName()));
    m_ui->lineEdit_stadLocation->setText(QString::fromStdString(stadium.getLocation()));
    m_ui->lineEdit_stadTeamName->setText(QString::fromStdString(team.getName()));

    /* Fill combo boxes (1 is added since the initial is an empty string) */
    m_ui->comboBox_stadTeamLeague->setCurrentIndex(team.league + 1);
    m_ui->comboBox_stadRoof->setCurrentIndex(stadium.roof + 1);
    m_ui->comboBox_stadSurface->setCurrentIndex(stadium.surface + 1);
    m_ui->comboBox_stadTypology->setCurrentIndex(stadium.typology + 1);

    /* Fill spin boxes */
    m_ui->spinBox_stadYearOpened->setValue(stadium.getYearOpened());
    m_ui->spinBox_stadSeatCap->setValue(stadium.getSeatCap());
    m_ui->spinBox_stadCenterDist->setValue(stadium.getCenterFieldDist());
}

void AdminView::on_pushButton_stadEditSouvenirs_clicked()
{
    m_currentStadiumId = m_ui->spinBox->value(); //TODO replace with selected ID from stadium list

    /* Extract stadium from database and check if valid */
    const Stadium& stadium = Database::findStadiumById(m_currentStadiumId);
    if(stadium.getId() == -1)
        return;

    resetUi();
    m_ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Fill souvenir edit fields
 * @param souvenirId
 */
void AdminView::fillSouvenirEditFields(int souvenirId)
{
    /* Extract stadium from database and check if valid */
    Stadium stadium = Database::findStadiumById(m_currentStadiumId);
    if(stadium.getId() == -1)
        return;

    /* Extract souvenir and fill edit fields */
    const Souvenir& souvenir = stadium.findSouvenir(souvenirId);
    m_ui->lineEdit_souvEditName->setText(QString::fromStdString(souvenir.getName()));
    m_ui->doubleSpinBox_souvEditPrice->setValue(souvenir.getPrice());
}

/**
 * @brief Hide or resture currently selected souvenir from the either list
 */
void AdminView::on_pushButton_souvHideRestore_clicked()
{
    SouvenirId id = m_availableSouvenirList->getSelected().second;

    if(id == -1)
        id = m_hiddenSouvenirList->getSelected().second;

    if(id == -1)
        return;

    Stadium& stadium = Database::findStadiumById(m_currentStadiumId);
    Souvenir& souvenir = stadium.findSouvenir(id);

    //Flip the hidden state
    souvenir.hidden = !souvenir.hidden;
}

/**
 * Goes back to stadium list page by calling @a resetView().
 */
void AdminView::on_pushButton_souvGoBack_clicked()
{
    resetView();
}
