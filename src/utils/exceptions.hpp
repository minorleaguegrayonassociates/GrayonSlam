#pragma once
#include <QException>
#include <QMessageBox>
#include <QIcon>
#include <QFile>

/**
 * @class GeneralException class
 *
 * An exception class that is the base class for future derived
 * exception classes. An example derived exception class is BadFile.
 * The advantage of deriving exceptions from this class is that
 * you can open an error window when called. The only requirement
 * is setting the message; if the message isn't set and the error
 * window is called, an empty string will be shown on the window.
 *
 * @code{.cpp}
 * try
 * {
 *     throwsBadFileException();
 * }
 * catch(GeneralException& e)
 * {
 *     e.errorWindow();
 * }
 * @endcode
 *
 * In the code above, a BadFile exception is thrown. We then
 * have a catch block that catches any exception derived from
 * GeneralException (which BadFile does). We then open an error
 * window that displays the information string that was given
 * to the throw exception.
 */
class GeneralException : public QException
{
public:
    /**
     * Creates an exception with an empty exception message.
     */
    GeneralException() {}

    /**
     * Creates an exception with a exception message.
     *
     * @param msg Exception message
     */
    GeneralException(QString msg)
        : m_msg(msg)
    {}

    /**
     * @brief Open error window with message
     *
     * When caught, call this in order to display information
     * to the screen about the exception.
     */
    void errorWindow() const
    {
        QMessageBox error(QMessageBox::Critical, "Error", m_msg);
        error.setWindowIcon(QIcon(":/res/Minor_League_Grayons_With_Arms.png"));
        error.exec();
    }

    /**
     * Returns the error message that was set before thrown.
     *
     * @return Error message
     */
    QString errorMessage() const
    {
        return m_msg;
    }

    /**
     * QException requires this to be overrided
     */
    void raise() const override
    {
        throw *this;
    }

    /**
     * QException requires this to be overrided
     *
     * @return A duplicate of this object
     */
    GeneralException* clone() const override
    {
        return new GeneralException(*this);
    }

protected:
    QString m_msg;
};

/**
 * @class BadFile class
 *
 * An exception class that derives from GeneralException.
 * This is mainly used to throw exceptions when a file
 * can't be opened.
 */
class BadFile : public GeneralException
{
public:
    /**
     * Creates an exception with a exception message.
     *
     * @param msg Exception message
     */
    BadFile(QString msg)
        : GeneralException(msg)
    {}

    /**
     * Creates an exception with an exception message
     * using the file's name.
     *
     * @param expected Expected from file input
     * @param recieved Received from file input
     */
    BadFile(const QFile& file)
    {
        m_msg = "Failed to use file!\n" + file.fileName();
    }
};

/**
 * @class BadFileFormat class
 *
 * An exception class that derives from GeneralException.
 * This is mainly used to throw exceptions when inputting
 * from a file and there is an invalid input.
 */
class BadFileFormat : public GeneralException
{
public:
    /**
     * Creates an exception with a exception message.
     *
     * @param msg Exception message
     */
    BadFileFormat(QString msg)
        : GeneralException(msg)
    {}

    /**
     * @brief Error message with expected and Received values
     *
     * A way to create an error message giving only what was
     * expected and what was received when inputting.
     *
     * @param expected Expected from file input
     * @param recieved Received from file input
     */
    BadFileFormat(QString expected, QString received)
    {
        m_msg = "Expected: " + expected + "\n" +
                "Recieved: " + received;
    }

    /**
     * @brief Error message with expected and received values
     *        at a line number
     *
     * Similar to the other constructor that takes in a
     * expected and received string, but this one adds a line
     * number to the error message.
     *
     * @param expected Expected from file input
     * @param recieved Received from file input
     * @param lineNum Line number error occurred
     */
    BadFileFormat(QString expected, QString received, int lineNum)
        : BadFileFormat(expected, received)
    {
        m_msg += "\nLine: " + QString::number(lineNum);
    }
};

