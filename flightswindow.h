#ifndef FLIGHTSWINDOW_H
#define FLIGHTSWINDOW_H

#include <QMainWindow>

namespace Ui {
class flightsWindow;
}

class flightsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit flightsWindow(QWidget *parent = nullptr);
    ~flightsWindow();

private slots:
    void on_backBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::flightsWindow *ui;
};

#endif // FLIGHTSWINDOW_H
