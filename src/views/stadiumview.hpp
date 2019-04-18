#pragma once

#include <QWidget>
#include "view.hpp"

namespace Ui {
class StadiumView;
}

class StadiumView : public View
{
    Q_OBJECT

public:
    explicit StadiumView(QWidget *parent = nullptr);
    ~StadiumView();
    virtual void resetView();
    virtual void resetUI();

private:
    Ui::StadiumView *ui;
};