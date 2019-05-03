#pragma once
#include <QWidget>

/**
 * @class View class
 *
 * View is an abstract base class that defines 2 basic functions that
 * views must define: resetView() and resetUi().
 */
class View: public QWidget
{
    Q_OBJECT
    
public:
    explicit View(QWidget* parent)
        : QWidget(parent)
    {}
    virtual ~View(){}
    /**
     * The resetView function resets any internal components of the view.
     */
    virtual void resetView() = 0;

    /**
     * The resetUi function resets the Ui that corresponds with the given view
     */
    virtual void resetUi() = 0;
};
