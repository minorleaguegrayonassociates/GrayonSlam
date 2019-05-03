#include "login.hpp"
#include "ui_login.h"
#include "utils/exceptions.hpp"
#include <QCryptographicHash>
#include <QTextStream>
#include <QTimer>
#include <QDir>

/* Static variables */
Login::Type   Login::type         = Login::Type::USER;
Login*        Login::instance     = nullptr;
const QString Login::FILE_NAME    = "credFile.txt";
const QString Login::FILE_PATH    = "";
const QString Login::FILE_ERR_MSG = "Authentication failed, contact admin!";

/**
 * If there isn't a current instance, one will be created as
 * well as the credential file.
 *
 * @return Singleton instance
 */
Login* Login::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Login;

        /* Initialize the credential file if it doesn't exist */
        QFile authFile(FILE_PATH + FILE_NAME);
        authFile.open(QIODevice::NewOnly);
    }

    return instance;
}

/**
 * Returns the login type of the last user that logged in
 *
 * @return Login type of the last user that logged in
 */
Login::Type Login::getType()
{
    return type;
}

/**
 * @brief Show the login window
 *
 * Calls getInstance() in case it hasn't been called yet.
 */
void Login::requestLogin()
{
    //Initializes the singleton object just in case
    getInstance();

    instance->resetUi();
    instance->clearFields();
    instance->show();
}

/**
 * @brief Login request button
 *
 * Upon clicking the login button, obtain the login credential
 * fields and validate them. If any exception was throw, an
 * error window will show with details.
 */
void Login::on_pushButton_login_clicked()
{
    resetUi();

    try
    {
        QString username = m_ui->lineEdit_username->text();
        QString password = m_ui->lineEdit_password->text();

        authenticate(username, password);
    }
    catch(GeneralException& exception)
    {
        exception.errorWindow();
    }
}

/**
 * @brief Registration view button
 *
 * Clicking the register button will change the current view.
 */
void Login::on_pushButton_register_clicked()
{
    resetUi();

    m_ui->stackedWidget->setCurrentWidget(m_ui->page_register);
    m_ui->lineEdit_usernameReg->setFocus();
}

/**
 * @brief Show password button
 *
 * Toggling the show password checkbox will toggle the password
 * field between asterisks and letters.
 */
void Login::on_checkBox_showPW_stateChanged(int state)
{
    m_ui->lineEdit_password->setEchoMode((state == Qt::CheckState::Checked ? QLineEdit::EchoMode::Normal
                                                                           : QLineEdit::EchoMode::Password));
}

/**
 * @brief Confirm registration button
 *
 * Clicking the "confirm register" button will obtain the
 * registration credential fields and validate them.
 * If any exception was thrown, an error window will show with details.
 */
void Login::on_pushButton_confirmReg_clicked()
{
    resetUi();

    try
    {
        QString username = m_ui->lineEdit_usernameReg->text();
        QString password = m_ui->lineEdit_passwordReg->text();
        QString pwConfirm = m_ui->lineEdit_confirmPassword->text();

        registration(username, password, pwConfirm);
    }
    catch(GeneralException& exception)
    {
        exception.errorWindow();
    }
}

/**
 * @brief Cancel registration button
 *
 * Clicking the "cancel register" button will change the current view
 * to the login view.
 */
void Login::on_pushButton_cancelReg_clicked()
{
    resetUi();
    clearFields();

    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);
}

/**
 * The initial view will be set to the login page, and window flags
 * for a fixed window size will be set.
 */
Login::Login()
    : QDialog(nullptr), m_ui(new Ui::Login)
{
    m_ui->setupUi(this);
    setModal(true);

    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}

/**
 * @brief Authenticate credentials
 *
 * Validates the given credentials against the credentials file.
 * Exceptions are thrown if the file couldn't be opened in ReadOnly
 * mode and the file format is wrong. Sets the user type static
 * variable if the credentials are correct.
 *
 * @param usernameInput Username to authenticate
 * @param passwordInput Password to authenticate
 */
void Login::authenticate(QString usernameInput, QString passwordInput) const
{
    QFile authFile(FILE_PATH + FILE_NAME);
    QTextStream qin(&authFile);

    /* Check if file is open */
    if(!authFile.open(QIODevice::ReadOnly)) { throw BadFile(FILE_ERR_MSG); }

    /* Hash the user's input */
    usernameInput = hashString(usernameInput);
    passwordInput = hashString(passwordInput);

    /* Data from file */
    QString usernameFile;
    QString passwordFile;
    QString typeFile;

    /* Search for correct username and password */
    while(!qin.atEnd())
    {
        /* Get data from file */
        usernameFile = qin.readLine();
        passwordFile = qin.readLine();
        typeFile = qin.readLine();

        if(usernameFile.isEmpty() || passwordFile.isEmpty() || typeFile.isEmpty() ||
          (typeFile != "admin" && typeFile != "user"))
        {
            throw BadFileFormat(FILE_ERR_MSG);
        }
        else if(usernameFile == usernameInput && passwordFile == passwordInput)
        {
            type = (typeFile == "admin" ? Type::ADMIN : Type::USER);
            authSuccessful();
            return;
        }
    }

    authFailed();
}

/**
 * Displays to the user that the login was successful and accepts the dialog.
 */
void Login::authSuccessful() const
{
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: green; color: white; }");
    m_ui->label_loginMsg->setText("Login successful");

    //Delays the closing of the window
    QTimer::singleShot(250, instance, &QDialog::accept);
}

/**
 * Displays to the user that the login was unsuccessful.
 */
void Login::authFailed() const
{
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: red; color: white; }");
    m_ui->label_loginMsg->setText("Invalid login");
}

/**
 * @brief Register credentials
 *
 * Checks if any of the fields are invalid; if they are, call
 * regFailed() and return. Exceptions are thrown if the file
 * couldn't be opened in ReadWrite mode and the file format is wrong.
 * Checks against the file if the username given is unique, if
 * it isn't call regFailed() and return. If the registration is
 * good, write to the file the given credentials.
 *
 * @param usernameInput Username to register
 * @param passwordInput Password to register
 * @param pwConfirmed Confirmation password
 */
void Login::registration(QString usernameInput, QString passwordInput, QString pwConfirmed) const
{
    /* Check the validity of each input field */
    int flags = 0;

    if(usernameInput.isEmpty()) { flags |= RegField::UN; }
    if(passwordInput.isEmpty()) { flags |= RegField::PW; }
    if(pwConfirmed.isEmpty() || passwordInput != pwConfirmed) {flags |= RegField::CPW; }

    if(flags != 0)
    {
        regFailed(static_cast<RegField>(flags));
        return;
    }

    QFile authFile(FILE_PATH + FILE_NAME);
    QTextStream qin(&authFile);

    /* Check if file is open */
    if(!authFile.open(QIODevice::ReadWrite)) { throw BadFile(FILE_ERR_MSG); }

    QString usernameFile;
    usernameInput = hashString(usernameInput);

    /* Search for a matching username or data error in file */
    while(!qin.atEnd())
    {
        usernameFile = qin.readLine();

        if(qin.readLine().isEmpty() || qin.readLine().isEmpty()) //Skips the next 2 lines
        {
            throw BadFileFormat(FILE_ERR_MSG);
        }
        else if(usernameInput == usernameFile)
        {
            regFailed(RegField::UN);
            return;
        }
    }

    //Write credentials to the end of file
    qin << usernameInput << endl
        << hashString(passwordInput) << endl
        << "user" << endl;

    regSuccessful();
}

/**
 * Grabs the newly registered username and puts it in the
 * login username field. Changes the view to the login view
 * and displays that the registration was successful.
 */
void Login::regSuccessful() const
{
    /* Grab the new user's username and store it into the login */
    QString newUserUsername = m_ui->lineEdit_usernameReg->text();
    clearFields();
    m_ui->lineEdit_username->setText(newUserUsername);

    m_ui->stackedWidget->setCurrentWidget(m_ui->page_login);
    m_ui->label_loginMsg->setStyleSheet("QLabel { background-color: green; color: white; }");
    m_ui->label_loginMsg->setText("Registration successful");
}

/**
 * If no flags are set, return. Sets the flag's respective field to red.
 *
 * @param fieldFlags Fields that were invalid
 */
void Login::regFailed(RegField fieldFlags) const
{
    if(fieldFlags == 0) { return; }

    QString txtStyle = "QLabel { color: red; }";

    /* Initializing the labels with the error marker */
    m_ui->label_regMsg->setText("Invalid fields (*)");
    m_ui->label_regMsg->setStyleSheet(txtStyle);
    m_ui->label_usernameReg->setText("*");
    m_ui->label_passwordReg->setText("*");
    m_ui->label_confirmPassword->setText("*");

    /* Bitwise operations to see if a flag is are set for each flag */
    if((fieldFlags & 0b1)   == RegField::UN)  { m_ui->label_usernameReg->setStyleSheet(txtStyle); }
    if((fieldFlags & 0b10)  == RegField::PW)  { m_ui->label_passwordReg->setStyleSheet(txtStyle); }
    if((fieldFlags & 0b100) == RegField::CPW) { m_ui->label_confirmPassword->setStyleSheet(txtStyle); }
}

/**
 * @brief Hash function
 *
 * Returns a hashed version of the given string with a cryptographic hash function.
 *
 * @param string String to hash
 * @return Hashed string
 */
QByteArray Login::hashString(QString string) const
{
    return QCryptographicHash::hash(string.toStdString().data(), QCryptographicHash::Keccak_512).toHex();
}

/**
 * Resets the background and text colors of labels. Also clears
 * message labels.
 */
void Login::resetUi() const
{
    QString bgStyle = "QLabel { background-color: transparent; }";
    QString txtStyle = "QLabel { color: transparent; }";

    /* Background color */
    m_ui->label_regMsg->setStyleSheet(bgStyle);
    m_ui->label_loginMsg->setStyleSheet(bgStyle);

    /* Text color */
    m_ui->label_usernameReg->setStyleSheet(txtStyle);
    m_ui->label_passwordReg->setStyleSheet(txtStyle);
    m_ui->label_confirmPassword->setStyleSheet(txtStyle);

    /* Text */
    m_ui->label_loginMsg->setText("");
    m_ui->label_regMsg->setText("");

    m_ui->lineEdit_username->setFocus();
}

/**
 * Clears all the text input fields.
 */
void Login::clearFields() const
{
    m_ui->lineEdit_password->setText("");
    m_ui->lineEdit_usernameReg->setText("");
    m_ui->lineEdit_passwordReg->setText("");
    m_ui->lineEdit_confirmPassword->setText("");
}
