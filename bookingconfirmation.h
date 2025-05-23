#ifndef BOOKINGCONFIRMATION_H
#define BOOKINGCONFIRMATION_H

#include <QDialog>

namespace Ui
{
    class BookingConfirmation;
}

class BookingConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit BookingConfirmation(double totalCost, QWidget *parent = nullptr);
    ~BookingConfirmation();

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::BookingConfirmation *ui;
    double totalCost;
};

#endif // BOOKINGCONFIRMATION_H