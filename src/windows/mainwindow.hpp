#pragma once
#include <QMainWindow>
#include <vector>
#include "src/widgets/navbar.hpp"
#include "src/views/view.hpp"

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

    void on_pushButton_clicked();

private:
    graph* m_graph;
    Ui::MainWindow* m_ui;
    NavBar* m_navbar;
    std::vector<View*> m_views;
};

