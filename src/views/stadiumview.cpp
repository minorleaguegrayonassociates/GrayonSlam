#include "stadiumview.hpp"
#include "ui_stadiumview.h"

/**
 * Constructs a Stadium View with a pointer to the parent widget which it will reside in
 *
 * @param parent pointer to widget it will reside in
 */
StadiumView::StadiumView(QWidget* parent) :
    View(parent),
    ui(new Ui::StadiumView)
{
    //Initialize Ui
    ui->setupUi(this);

    //Instantiate and populate tree widget
    m_stadiumList = new StadiumList(ui->stadiumList);
    m_stadiumList->populateWidget(Database::getTeamsAndStadiums());
}

/**
 * Destructor deletes the Ui and the tree widget
 */
StadiumView::~StadiumView()
{
    delete ui;
    delete m_stadiumList;
}

/**
 * resetView() clears all of its children and repopulates the widgets
 * from the database
 */
void StadiumView::resetView()
{
    //clear all data, get it new from database, and populate table
    m_stadiumList->populateWidget(Database::getTeamsAndStadiums());
}

/**
 * resetUi() repopulates the tree widget from the database
 */
void StadiumView::resetUi()
{
    //clear table and repopulate it with list
    m_stadiumList->populateWidget(Database::getTeamsAndStadiums());
}
