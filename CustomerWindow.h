#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CustomerWindow;
}
QT_END_NAMESPACE

class CustomerWindow : public QMainWindow
{
    Q_OBJECT

public:
    CustomerWindow(QWidget *parent = nullptr);
    ~CustomerWindow();

private slots:
    void on_flightwinBtn_clicked();

    void on_hotelswinBtn_clicked();

private:
    Ui::CustomerWindow *ui;
};
#endif // CUSTOMERWINDOW_H
