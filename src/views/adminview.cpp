#include "adminview.hpp"
#include "ui_adminview.h"
#include "src/datastore/database.hpp"
#include <QFileDialog>
#include <QTimer>

AdminView::AdminView(QWidget* parent)
    : View(parent), m_ui(new Ui::AdminView)
{
    m_ui->setupUi(this);

    /* Initialize stadium list */
    m_stadiumList = new StadiumList(m_ui->widget_stadList);

    /* Initialize souvenir lists */
    m_availableSouvenirList = new SouvenirList(m_ui->widget_souvAvailableList);
    m_hiddenSouvenirList = new SouvenirList(m_ui->widget_souvHiddenList);
    m_hiddenSouvenirList->allowHidden(true);

    /*
     * This connection will change the current stadium ID to the
     * new stadium ID that is emitted by the stadium list and
     * the stadium edit fields are filled
     */
    connect(m_stadiumList, &StadiumList::stadiumClicked,
            [&](int id)
            {
                m_currentStadiumId = id;
                fillStadiumEditFields(id);
            });

    /*
     * These connections will unselect items of the other list and
     * fill the souvenir edit fields with the selected item
     */
    connect(m_availableSouvenirList, &SouvenirList::currentSouvenirChanged,
            [&](IDs ids)
            {
                m_hiddenSouvenirList->setCurrentRow(-1);
                fillSouvenirEditFields(ids.second);
            });

    connect(m_hiddenSouvenirList, &SouvenirList::currentSouvenirChanged,
            [&](IDs ids)
            {
                m_availableSouvenirList->setCurrentRow(-1);
                fillSouvenirEditFields(ids.second);
            });

    resetView();
}

/**
 * Deletes all the widgets in the view.
 */
AdminView::~AdminView()
{
    delete m_ui;
    delete m_stadiumList;
    delete m_availableSouvenirList;
    delete m_hiddenSouvenirList;
}

/**
 * Resets the admin view as if it was just created.
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
    Database::saveToFile("MLBInformation.csv");

    fillStadiumList();
    fillSouvenirLists(m_currentStadiumId);

    /* Line edits */
    m_ui->lineEdit_stadName->clear();
    m_ui->lineEdit_stadLocation->clear();
    m_ui->lineEdit_stadTeamName->clear();
    m_ui->lineEdit_souvAddName->clear();
    m_ui->lineEdit_souvEditName->clear();

    /* Combo boxes */
    m_ui->comboBox_stadTeamLeague->setCurrentIndex(0);
    m_ui->comboBox_stadRoof->setCurrentIndex(0);
    m_ui->comboBox_stadSurface->setCurrentIndex(0);
    m_ui->comboBox_stadTypology->setCurrentIndex(0);

    /* Spin boxes */
    m_ui->spinBox_stadYearOpened->clear();
    m_ui->spinBox_stadSeatCap->clear();
    m_ui->spinBox_stadCenterDist->clear();
    m_ui->doubleSpinBox_souvAddPrice->clear();
    m_ui->doubleSpinBox_souvEditPrice->clear();

    /* Check boxes */
    m_ui->checkBox_souvAddHidden->setCheckState(Qt::CheckState::Unchecked);
    m_ui->checkBox_souvEditHidden->setCheckState(Qt::CheckState::Unchecked);
}

/**
 * @brief Clear and load stadium list
 *
 * Obtains all the team and stadium information from the database.
 * All non-hidden stadiums are loaded into the stadium list.
 */
void AdminView::fillStadiumList()
{
    m_stadiumList->populateWidget(Database::getTeamsAndStadiums());
}

/**
 * @brief Clear and load souvenir lists
 *
 * A stadium object is extracted from the database using @a stadiumId.
 * The souvenirs of the extracted stadium is used to fill the
 * available and hidden souvenir lists. As a precaution, the lists
 * are cleared to remove any leftover items in the lists before fill.
 *
 * If the passed ID results in an invalid stadium, this function does nothing.
 *
 * @param stadiumId Stadium ID with souvenirs to use in the lists
 */
void AdminView::fillSouvenirLists(StadiumId stadiumId)
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
        (souvenir.hidden ? m_hiddenSouvenirList
                         : m_availableSouvenirList)->addItem(stadium.getId(), souvenir);
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
 * @param stadiumId ID of Stadium to fill the edit fields with
 */
void AdminView::fillStadiumEditFields(StadiumId stadiumId)
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

/**
 * @brief Get currently selected souvenir ID
 *
 * Returns the currently selected souvenir ID by checking
 * both available and hidden souvenir lists.
 *
 * @return Currently selected souvenir ID
 */
SouvenirId AdminView::getCurrentSouvenirId() const
{
    SouvenirId id = m_availableSouvenirList->getSelected().second;

    if(id == -1)
        id = m_hiddenSouvenirList->getSelected().second;

    return id;
}

/**
 * @brief Edit currently selected stadium
 *
 * Obtain input from UI and edit the currently selected stadium
 * with the input. Resets the UI to reload the stadium list.
 *
 * If the input is invalid (empty strings, invalid stadium ID,
 * or invalid enum indices), then this function does nothing.
 */
void AdminView::on_pushButton_stadConfirmEdit_clicked()
{
    /* Extract stadium from database and check if valid */
    Stadium& stadium = Database::findStadiumById(m_currentStadiumId);
    if(stadium.getId() == -1)
    {
        markButtonAsError(m_ui->pushButton_stadConfirmEdit);
        return;
    }

    //Extract team from database
    Team& team = Database::findTeamById(stadium.getTeamId());

    /* Line edits */
    const QString& stadName = m_ui->lineEdit_stadName->text();
    const QString& loc = m_ui->lineEdit_stadLocation->text();
    const QString& teamName = m_ui->lineEdit_stadTeamName->text();

    /* Spin boxes */
    int year = m_ui->spinBox_stadYearOpened->value();
    int cap = m_ui->spinBox_stadSeatCap->value();
    int dist = m_ui->spinBox_stadCenterDist->value();

    /*
     * Combo boxes
     *
     * NOTE:
     * Since each combo box has an empty string for the initial
     * value, we must subtract one from the value of the combo box
     * to get the expected value.
     */
    int leagueIndex = m_ui->comboBox_stadTeamLeague->currentIndex() - 1;
    int roofIndex = m_ui->comboBox_stadRoof->currentIndex() - 1;
    int surfaceIndex = m_ui->comboBox_stadSurface->currentIndex() - 1;
    int typologyIndex = m_ui->comboBox_stadTypology->currentIndex() - 1;

    /* Error check input */
    if(stadName.isEmpty() || loc.isEmpty()   || teamName.isEmpty() ||
       leagueIndex == -1  || roofIndex == -1 ||
       surfaceIndex == -1 || typologyIndex == -1)
    {
        markButtonAsError(m_ui->pushButton_stadConfirmEdit);
        return;
    }

    /* Enum conversions */
    Team::League league = static_cast<Team::League>(leagueIndex);
    Stadium::Roof roof = static_cast<Stadium::Roof>(roofIndex);
    Stadium::Surface surface = static_cast<Stadium::Surface>(surfaceIndex);
    Stadium::Typology typology = static_cast<Stadium::Typology>(typologyIndex);

    /* Edit stadium */
    stadium.setName(stadName.toStdString());
    stadium.setLocation(loc.toStdString());
    stadium.setYearOpened(year);
    stadium.setSeatCap(cap);
    stadium.setCenterFieldDist(dist);
    stadium.roof = roof;
    stadium.surface = surface;
    stadium.typology = typology;

    /* Edit team */
    team.setName(teamName.toStdString());
    team.league = league;

    resetUi();
}

/**
 * @brief Add stadiums and their distances from a file into the database
 *
 * Prompt for a stadium information file that holds information about the
 * new stadiums. Once that is completed, prompt for a stadium distances
 * information file that holds information about the distances of the
 * new stadiums. Tell the database to load these new files into itself.
 *
 * The required file extensions is @a .csv.
 *
 * If either prompts are cancelled, this function does nothing.
 */
void AdminView::on_pushButton_stadAddFromFile_clicked()
{
    /* Prompt for stadium info file and check if request was cancelled */
    QString stadFile = QFileDialog::getOpenFileName(this, "Add stadiums", QDir::homePath(), "Stadium information file (*.csv)");
    if(stadFile.isEmpty())
    {
        markButtonAsError(m_ui->pushButton_stadAddFromFile);
        return;
    }

    /* Prompt for stadium distances info file and check if request was cancelled */
    QString distFile = QFileDialog::getOpenFileName(this, "Add distances", QDir::homePath(), "Distances information file (*.csv)");
    if(distFile.isEmpty())
    {
        markButtonAsError(m_ui->pushButton_stadAddFromFile);
        return;
    }


    /* Use the files to load data into the database */
    Database::loadFromFile(stadFile.toStdString());
    Database::loadDistancesFromFile(distFile.toStdString());
}

/**
 * @brief Change to souvenir page
 *
 * Obtains the currently selected stadium from the stadium list.
 * The UI is reset and the stacked widget page is changed to
 * the souvenir page.
 *
 * If the ID of the currently selected stadium is an invalid
 * ID (-1), this function does nothing besides store the ID.
 */
void AdminView::on_pushButton_stadEditSouvenirs_clicked()
{
    /* Extract stadium from database and check if valid */
    const Stadium& stadium = Database::findStadiumById(m_currentStadiumId);
    if(stadium.getId() == -1)
    {
        markButtonAsError(m_ui->pushButton_stadEditSouvenirs);
        return;
    }


    resetUi();

    //Change to souvenir page
    m_ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Fill souvenir edit fields
 *
 * Fills all the souvenir edit fields with information about a
 * souvenir that is represented by @a souvenirId.
 *
 * The stadium used to determine which souvenirs to get is
 * determined by @a m_currentStadiumId.
 *
 * @param souvenirId ID of Souvenir of @a m_currentStadiumId to fill the edit fields with
 */
void AdminView::fillSouvenirEditFields(SouvenirId souvenirId)
{
    /* Extract stadium from database and check if valid */
    const Stadium& stadium = Database::findStadiumById(m_currentStadiumId);
    if(stadium.getId() == -1)
        return;

    /* Extract souvenir and fill edit fields */
    const Souvenir& souvenir = stadium.findSouvenir(souvenirId);
    m_ui->lineEdit_souvEditName->setText(QString::fromStdString(souvenir.getName()));
    m_ui->doubleSpinBox_souvEditPrice->setValue(souvenir.getPrice());
    m_ui->checkBox_souvEditHidden->setCheckState(souvenir.hidden ? Qt::CheckState::Checked
                                                                 : Qt::CheckState::Unchecked);
}

/**
 * @brief Edit currently selected souvenir
 *
 * Obtain input from UI and edit the currently selected souvenir
 * with the input. Resets the UI to reload the souvenir lists.
 *
 * If the input is invalid (empty strings, invalid souvenir ID,
 * or 0 for price), then this function does nothing.
 */
void AdminView::on_pushButton_souvConfirmEdit_clicked()
{
    /* Extract input from UI */
    const QString& name = m_ui->lineEdit_souvEditName->text();
    double price = m_ui->doubleSpinBox_souvEditPrice->value();
    bool hidden = m_ui->checkBox_souvEditHidden->checkState() == Qt::CheckState::Checked;

    /* Error check currently selected souvenir and input */
    SouvenirId id = getCurrentSouvenirId();
    if(id == -1 || name.isEmpty() || price == 0.0)
    {
        markButtonAsError(m_ui->pushButton_souvConfirmEdit);
        return;
    }

    /* Extract stadium and souvenir from database */
    Stadium& stadium = Database::findStadiumById(m_currentStadiumId);
    Souvenir& souvenir = stadium.findSouvenir(id);

    /* Change souvenir data */
    souvenir.setName(name.toStdString());
    souvenir.setPrice(price);
    souvenir.hidden = hidden;

    resetUi();
}

/**
 * @brief Add new souvenir to the stadium
 *
 * Obtain input from UI and add a new souvenir to the stadium.
 * Resets the UI to reload the souvenir lists.
 *
 * If the input is invalid (empty strings, invalid souvenir ID,
 * or 0 for price), then this function does nothing.
 */
void AdminView::on_pushButton_souvConfirmAdd_clicked()
{
    /* Extract input from UI */
    const QString& name = m_ui->lineEdit_souvAddName->text();
    double price = m_ui->doubleSpinBox_souvAddPrice->value();
    bool hidden = m_ui->checkBox_souvAddHidden->checkState() == Qt::CheckState::Checked;

    /* Error check input */
    if(name.isEmpty() || price == 0.0)
    {
        markButtonAsError(m_ui->pushButton_souvConfirmAdd);
        return;
    }

    /* Extract stadium and souvenir from database */
    Stadium& stadium = Database::findStadiumById(m_currentStadiumId);
    stadium.addSouvenir(name.toStdString(), price, hidden);

    resetUi();
}

/**
 * Goes back to stadium list page by calling @a resetView().
 */
void AdminView::on_pushButton_souvReturn_clicked()
{
    resetView();
}

/**
 * @brief Mark a button with an error
 *
 * Takes a button and changes the text color to red to signify
 * and error has happened. After 2000 milliseconds, the stylesheet
 * is returned to its original setting.
 *
 * @param button Button to mark with error
 */
void AdminView::markButtonAsError(QPushButton* button)
{
    QString style = button->styleSheet();
    button->setStyleSheet("QPushButton { color: red; }");
    QTimer::singleShot(2000, [=]{ button->setStyleSheet(style); });
}
