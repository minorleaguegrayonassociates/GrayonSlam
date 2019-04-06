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
    explicit View(QWidget* parent = nullptr)
        : QWidget(parent)
    {}
    virtual ~View(){}
    /**
     * Resets any internal components of the view
     */
    virtual void resetView() = 0;

    /**
     * Resets the UI that corresponds with the given view
     */
    virtual void resetUi() = 0;
};
