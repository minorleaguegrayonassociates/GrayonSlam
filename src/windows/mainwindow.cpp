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
    Database::loadDistancesFromFile("./../../../src/datastore/DistanceBetweenStadiums.csv");
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
