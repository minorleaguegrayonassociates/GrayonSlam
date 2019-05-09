#include "src/windows/mainwindow.hpp"
#include "src/windows/login.hpp"
#include "src/datastore/database.hpp"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);

    MainWindow* window = nullptr;

    /* Copy the resource files into the filesystem */
    QFile(":/res/data-files/MLBInformation.csv").copy("MLBInformation.csv");
    QFile(":/res/data-files/DistanceBetweenStadiums.csv").copy("DistanceBetweenStadiums.csv");
    QFile(":/res/airplane.wav").copy("airplane.wav");
    QFile(":/res/splash.csv").copy("splash.csv");

    /* Set permissions for the new files */
    QFile mlbInfo("MLBInformation.csv");
    QFile distance("DistanceBetweenStadiums.csv");
    QFile airplaneWav(":/res/airplane.wav");
    mlbInfo.setPermissions(QFileDevice::Permissions(07700));
    distance.setPermissions(QFileDevice::Permissions(07700));
    airplaneWav.setPermissions(QFileDevice::Permissions(07700));

    /* Load data into database */
    Database::loadFromFile("MLBInformation.csv");
    Database::loadDistancesFromFile("DistanceBetweenStadiums.csv");

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
