#include "src/windows/mainwindow.hpp"
#include "src/datastore/parser.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    /* Loading in font - "Font Awesome 5 Free" */
    if(QFontDatabase::addApplicationFont(":/res/fontawesome-webfont.ttf") == -1)
        qWarning() << "FontAwesome cannot be loaded !";

    // Team Data File Path
    teamParseDebug("MLBInformation.csv");
    // Distance Data file path
    distanceParseDebug("DistanceBetweenStadiums.csv");
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
