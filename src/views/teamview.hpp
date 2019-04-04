#ifndef TEAMVIEW_HPP
#define TEAMVIEW_HPP

#include <QWidget>

namespace Ui {
class TeamView;
}

class TeamView : public QWidget
{
    Q_OBJECT

public:
    explicit TeamView(QWidget *parent = nullptr);
    ~TeamView();

private:
    Ui::TeamView *ui;
};

#endif // TEAMVIEW_HPP
