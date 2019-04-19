#pragma once

#include <QWidget>
#include "view.hpp"
#include "src/widgets/stadiumlist.hpp"
#include "src/datastore/database.hpp"


namespace Ui {
class StadiumView;
}

class StadiumView : public View
{
    Q_OBJECT

public:
    explicit StadiumView(QWidget *parent = nullptr);
    ~StadiumView() override;
    void resetView() override;
    void resetUi() override;

private:
    Ui::StadiumView *ui;
    StadiumList* m_stadiumList;
};
