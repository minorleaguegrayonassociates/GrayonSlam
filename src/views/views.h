#pragma once
#include <QWidget>

class AbstractViewModel
{
    Q_OBJECT
public:
    virtual void resetView() = 0;
    virtual void resetUI();
    virtual ~AbstractViewModel();
};
