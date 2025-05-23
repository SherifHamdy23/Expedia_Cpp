#ifndef MYBOOKINGS_H
#define MYBOOKINGS_H

#include <QMainWindow>

namespace Ui
{
    class MyBookings;
}

class MyBookings : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyBookings(QWidget *parent = nullptr);
    ~MyBookings();

private slots:
    void on_backButton_clicked();

private:
    Ui::MyBookings *ui;
};

#endif // MYBOOKINGS_H