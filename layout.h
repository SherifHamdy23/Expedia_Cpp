#ifndef LAYOUT_H
#define LAYOUT_H

#include <QMainWindow>

namespace Ui {
class Layout;
}

class Layout : public QMainWindow
{
    Q_OBJECT

public:
    explicit Layout(QWidget *parent = nullptr);
    ~Layout();

private:
    Ui::Layout *ui;
};

#endif // LAYOUT_H
