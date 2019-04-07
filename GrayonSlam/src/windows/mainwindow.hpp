#pragma once

#include <QMainWindow>
#include "src/widgets/navbar.hpp"

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
};

