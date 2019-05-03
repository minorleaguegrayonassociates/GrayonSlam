#ifndef GRAPHVIEW_HPP
#define GRAPHVIEW_HPP

#include <QWidget>

namespace Ui {
class GraphView;
}

class GraphView : public QWidget
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    ~GraphView();

private:
    Ui::GraphView *ui;
};

#endif // GRAPHVIEW_HPP
