#pragma once
#include <QListWidget>

namespace Ui
{
class NavBarItem;
}

class NavBarItem : public QWidget
{
    Q_OBJECT

public:
    /* Constructor */
    NavBarItem(QListWidget* parent, QString icon, QString label);

    /* Destructor */
    ~NavBarItem() override;

public slots:
    void expand() const;
    void shrink() const;

private:
    /* Events */
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

    Ui::NavBarItem* m_ui;
};
