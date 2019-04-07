#include "src/windows/mainwindow.hpp"
#include "src/windows/login.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);

    MainWindow* window = nullptr;

    /*
     * Connect the login object's accepted signal.
     *
     * When login is accepted, create a main window and show it;
     * at the same time, create a connection with the newly
     * created main window's logout signal.
     *
     * When the main window emits a logout, request that it be
     * deleted later and request another login.
     */
    QObject::connect(Login::getInstance(), &Login::accepted,
    [&]()
    {
        window = new MainWindow;
        window->show();

        QObject::connect(window, &MainWindow::logout,
        [&]()
        {
            window->deleteLater();
            Login::requestLogin();
        });
    });

    Login::requestLogin();

    return a.exec();
}
