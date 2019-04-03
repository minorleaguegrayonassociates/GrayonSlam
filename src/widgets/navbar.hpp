#pragma once
#include <QListWidget>

/**
 * @class NavBar class
 *
 * Provides an easy way to list clickable buttons.
 * Currently, the class uses "Font Awesome 5 Free" for its icons.
 *
 * To use:
 * @code{.cpp}
 * NavBar* navbar = new NavBar(widget, 50, 100);
 * navbar->addItems("\uffff", "Button");
 * @endcode
 *
 * This will instantiate the bar under the widget with a
 * minimum width of 50 and maximum width of 100.
 * Then it will add a button with the icon "\uffff"
 * from the "Font Awesome 5 Free" font and a label "Button".
 *
 * @see <a href="https://fontawesome.com/icons?d=gallery&m=free">Font Awesome icon reference</a>
 */
class NavBar : public QListWidget
{
    Q_OBJECT

public:
    /* Constructor */
    NavBar(QWidget* parent, int minWidth, int maxWidth);

    /* Setters */
    void setHeight(int);
    void setMinWidth(int);
    void setMaxWidth(int);

    /* List modifiers */
    void addItem(QString icon, QString label);

signals:
    void expand();
    void shrink();

private:
    /* Events */
    void leaveEvent(QEvent*) override;
    void enterEvent(QEvent*) override;

    /* Data Members */
    int m_minWidth;
    int m_maxWidth;
};
