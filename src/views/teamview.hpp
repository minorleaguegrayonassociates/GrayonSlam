#ifndef TEAMVIEW_HPP
#define TEAMVIEW_HPP

#include "abstractview.hpp"

namespace Ui {
class TeamView;
}

class TeamView : public AbstractViewModel
{
    Q_OBJECT

public:
    virtual void resetView();
    virtual void resetUI();
    explicit TeamView(QWidget *parent = nullptr);
    ~TeamView();

private:
    Ui::TeamView *ui;
};

#endif // TEAMVIEW_HPP
