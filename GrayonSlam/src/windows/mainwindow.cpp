#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "src/windows/login.hpp"
#include "src/datastore/database.hpp"
#include <QMessageBox>
#include <QDebug>
#include <QFontDatabase>
#include <iostream>
#include <vector>
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
    Database::loadFromFile("./../../../src/datastore/MLBInformationExpansion.csv");
    Database::loadFromFile("./../../../src/datastore/MLBInformation.csv");
    std::vector<Souvenir> tempSouvenir;
    std::map<int,Team> tempTeam(Database::getTeams());
    std::map<int,Stadium> tempStadium(Database::getStadiums());
    for(std::map<int,Team>::iterator it = tempTeam.begin(); it != tempTeam.end(); ++it)
    {
        std::cout << "----------Team ID: " << it->second.getId() << std::endl;
        std::cout << "--------Team Name: " << it->second.getName() << std::endl;
        std::cout << "---------Deleted?: " << it->second.hidden << std::endl;
        std::cout << "-------Stadium ID: " << it->second.getStadiumId() << std::endl;
        std::cout << "-----Stadium Name: " << Database::findStadiumById(it->second.getStadiumId()).getName() << std::endl;
        std::cout << "-Seating Capacity: " << Database::findStadiumById(it->second.getStadiumId()).getSeatCap() << std::endl;
        std::cout << "----Team Location: " << Database::findStadiumById(it->second.getStadiumId()).getLocation() << std::endl;
        std::cout << "--Playing Surface: " << Database::findStadiumById(it->second.getStadiumId()).surface << std::endl;
        std::cout << "-----------League: " << it->second.league << std::endl;
        std::cout << "------Date opened: " << Database::findStadiumById(it->second.getStadiumId()).getYearOpened() << std::endl;
        std::cout << "--Distance2CtrFld: " << Database::findStadiumById(it->second.getStadiumId()).getCenterFieldDist() << std::endl;
        std::cout << "Ballpark typology: " << Database::findStadiumById(it->second.getStadiumId()).typology << std::endl;
        std::cout << "--------Roof Type: " << Database::findStadiumById(it->second.getStadiumId()).roof << std::endl;

        tempSouvenir = Database::findStadiumById(it->second.getStadiumId()).getSouvenirs();

        std::cout << "Num. of souvenirs: "<< tempSouvenir.size() << std::endl;

        for(const Souvenir& item: tempSouvenir)
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
        else
        {
            m_navbar->setCurrentRow(m_ui->mainViews->currentIndex());
        }

    }
    else if(view == 3 && type == Login::Type::ADMIN) //Admin view
    {
        m_ui->mainViews->setCurrentIndex(view);
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
}
