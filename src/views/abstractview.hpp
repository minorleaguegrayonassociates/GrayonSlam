#pragma once
#include <QWidget>

/**
 * @class AbstractViewModel class
 *
 * An abstract base class that defines 2 basic functions that
 * views must define: resetView() and resetUI()
 */
class AbstractViewModel: public QWidget
{
    Q_OBJECT
public:

    virtual void resetView() = 0;

    /**
     * Resets the UI that corresponds with the given view
     */
    virtual void resetUI();

    explicit AbstractViewModel(QWidget* parent = nullptr): QWidget(parent){}
    virtual ~AbstractViewModel();
};
