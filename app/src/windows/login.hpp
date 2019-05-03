#pragma once
#include <QDialog>
#include <QByteArray>

namespace Ui { class Login; }

/**
 * @brief Login class
 *
 * Provides a simple way to request a login in order to validate a user.
 *
 * To use:
 * @code{.cpp}
 * QObject::connect(Login::getInstance(), &Login::accepted,
 *                  myWidgetPointer, &MyClass::mySlot);
 * @endcode
 *
 * This will call &MyClass::mySlot upon myWidgetPointer when login is accepted.
 */
class Login : public QDialog
{
    Q_OBJECT

public:
    enum class Type { USER, ADMIN };

    /* Getters */
    static Login* getInstance();
    static Type getType();

    /* Login usage */
    static void requestLogin();

private slots:
    /* Login page */
    void on_pushButton_login_clicked();
    void on_pushButton_register_clicked();
    void on_checkBox_showPW_stateChanged(int);

    /* Registration page */
    void on_pushButton_confirmReg_clicked();
    void on_pushButton_cancelReg_clicked();

private:
    enum RegField { UN = 0b1, PW = 0b10, CPW = 0b100 };

    /* Constructor */
    Login();

    /* Deleted members */
    Login(const Login&) = delete;
    void operator=(const Login&) = delete;

    /* Authentication handling */
    void authenticate(QString username, QString password) const;
    void authSuccessful() const;
    void authFailed() const;

    /* Registration handling */
    void registration(QString username, QString password, QString pwConfirmed) const;
    void regSuccessful() const;
    void regFailed(RegField) const;

    /* Hash algorithm */
    QByteArray hashString(QString string) const;

    /* Ui */
    void resetUi() const;
    void clearFields() const;

    /* Data members */
    Ui::Login* m_ui;

    /* Static variables */
    static Type type;
    static Login* instance;
    static const QString FILE_NAME;
    static const QString FILE_PATH;
    static const QString FILE_ERR_MSG;
};
