#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "src/windows/login.hpp"
#include "src/datastore/database.hpp"
#include <QFontDatabase>
#include <QMessageBox>
#include <QDebug>

/* Constructors */
MainWindow::MainWindow()
    : QMainWindow(nullptr),m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    //Doesn't allow window resizing
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    /* Loading in font - "Font Awesome 5 Free" */
    if(QFontDatabase::addApplicationFont(":/res/fontawesome-webfont.ttf") == -1){qWarning() << "FontAwesome cannot be loaded !";}

    /* Initialize navigation bar and items */
    m_navbar = new NavBar(m_ui->NavBarWidget, 90, 220);
    connect(m_navbar, &NavBar::currentRowChanged, this, &MainWindow::changeView);
    m_navbar->addItem("\uf0c9", "Dashboard");
    m_navbar->addItem("\uf5b0", "Plan\na Vacation");
    m_navbar->addItem("\uf433", "View\nTeams");
    if(Login::getType() == Login::Type::ADMIN)
        m_navbar->addItem("\uf085", "Inventory\nManagement");
    m_navbar->addItem("\uf2f5", "Logout");

    Database::loadFromFile("./../../../src/datastore/MLBInformation.csv");
    std::vector<Souvenir> tempSouvenir;
    nstd::map<int,Team> tempTeam(Database::getTeams());
    nstd::map<int,Stadium> tempStadium(Database::getStadiums());
    for(nstd::map<int,Team>::iterator it = tempTeam.begin(); it != tempTeam.end(); ++it)
    {
        std::cout << "----------Team ID: " << it->getId() << std::endl;
        std::cout << "--------Team Name: " << it->getName() << std::endl;
        std::cout << "---------Deleted?: " << it->hidden << std::endl;
        std::cout << "-------Stadium ID: " << it->getStadiumId() << std::endl;
        std::cout << "-----Stadium Name: " << tempStadium[it->getStadiumId()].getName() << std::endl;
        std::cout << "-Seating Capacity: " << tempStadium[it->getStadiumId()].getSeatCap() << std::endl;
        std::cout << "----Team Location: " << tempStadium[it->getStadiumId()].getLocation() << std::endl;
        std::cout << "--Playing Surface: " << tempStadium[it->getStadiumId()].surface << std::endl;
        std::cout << "-----------League: " << it->league << std::endl;
        std::cout << "------Date opened: " << tempStadium[it->getStadiumId()].getYearOpened() << std::endl;
        std::cout << "--Distance2CtrFld: " << tempStadium[it->getStadiumId()].getCenterFieldDist() << std::endl;
        std::cout << "Ballpark typology: " << tempStadium[it->getStadiumId()].typology << std::endl;
        std::cout << "--------Roof Type: " << tempStadium[it->getStadiumId()].roof << std::endl;

        tempSouvenir = tempStadium[it->getStadiumId()].getSouvenirs();

        std::cout << "Num. of souvenirs: "<< tempSouvenir.size() << std::endl;

        for(const Souvenir& item: tempSouvenir)
        {
            std::cout << "---------ID   " << item.getId() << std::endl;
            std::cout << "Is deleted?:  " << item.hidden << std::endl;
            std::cout << "---Souvenir:  " << item.getName() << std::endl;
            std::cout << "------Price:  " << item.getPrice()<< std::endl;
        }
    }
    std::vector<Souvenir> tempSouvenirVect;
    std::vector<Team> tempTeamVector(Database::getTeamsVector());
    std::vector<Stadium> tempStadiumVector(Database::getStadiumsVector());
    for(unsigned int i = 0; i < tempTeamVector.size(); ++i)
    {
        std::cout << "----------Team ID: " << tempTeamVector[i].getId() << std::endl;
        std::cout << "--------Team Name: " << tempTeamVector[i].getName() << std::endl;
        std::cout << "---------Deleted?: " << tempTeamVector[i].hidden << std::endl;
        std::cout << "-------Stadium ID: " << tempTeamVector[i].getStadiumId() << std::endl;
        std::cout << "-----Stadium Name: " << tempStadiumVector[i].getName() << std::endl;
        std::cout << "-Seating Capacity: " << tempStadiumVector[i].getSeatCap() << std::endl;
        std::cout << "----Team Location: " << tempStadiumVector[i].getLocation() << std::endl;
        std::cout << "--Playing Surface: " << tempStadiumVector[i].surface << std::endl;
        std::cout << "-----------League: " << tempTeamVector[i].league << std::endl;
        std::cout << "------Date opened: " << tempStadiumVector[i].getYearOpened() << std::endl;
        std::cout << "--Distance2CtrFld: " << tempStadiumVector[i].getCenterFieldDist() << std::endl;
        std::cout << "Ballpark typology: " << tempStadiumVector[i].typology << std::endl;
        std::cout << "--------Roof Type: " << tempStadiumVector[i].roof << std::endl;

        tempSouvenirVect = tempStadiumVector[i].getSouvenirs();

        std::cout << "Num. of souvenirs: "<< tempSouvenirVect.size() << std::endl;

        for(const Souvenir& item: tempSouvenirVect)
        {
            std::cout << "---------ID   " << item.getId() << std::endl;
            std::cout << "Is deleted?:  " << item.hidden << std::endl;
            std::cout << "---Souvenir:  " << item.getName() << std::endl;
            std::cout << "------Price:  " << item.getPrice()<< std::endl;
        }
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete m_navbar;
}

/* Private slots */
void MainWindow::changeView(int view)
{
    Login::Type type = Login::getType();

    /* Change view */
    if((view == 3 && type == Login::Type::USER) || //Logout
       (view == 4 && type == Login::Type::ADMIN))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Logout", "Are you sure you want to logout?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            emit logout();
        }
        else
        {
            m_navbar->setCurrentRow(m_ui->mainViews->currentIndex());
        }
    }
    else
    {
        resetViews();
        m_ui->mainViews->setCurrentIndex(view);
    }
}

void MainWindow::resetViews()
{
    /* Reset views -- go here */
    Database::saveToFile("./../../../src/datastore/MLBInformation.csv");
}
