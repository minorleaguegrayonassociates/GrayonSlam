#pragma once

#include <QDebug>
#include <QMainWindow>
#include <QFontDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void logout() const;

private:
    Ui::MainWindow *m_ui;
};

