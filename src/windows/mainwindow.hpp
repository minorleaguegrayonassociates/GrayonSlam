#pragma once
#include <QMainWindow>
#include <vector>
#include "widgets/navbar.hpp"
#include "views/view.hpp"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Constructors */
    MainWindow();

    /* Destructor */
    ~MainWindow() override;

signals:
    void logout() const;

private slots:
    void changeView(int);
    void resetViews();

private:
    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
    std::vector<View*> m_views;
};

