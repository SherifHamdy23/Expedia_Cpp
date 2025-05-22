#ifndef HOTELSWINDOW_H
#define HOTELSWINDOW_H

#include <QMainWindow>

namespace Ui {
class HotelsWindow;
}

class HotelsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HotelsWindow(QWidget *parent = nullptr);
    ~HotelsWindow();

private slots:
    void on_backBtn_clicked();

private:
    Ui::HotelsWindow *ui;
};

#endif // HOTELSWINDOW_H
