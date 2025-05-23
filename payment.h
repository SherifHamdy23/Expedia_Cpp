#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>

namespace Ui
{
    class Payment;
}

class Payment : public QDialog
{
    Q_OBJECT

public:
    explicit Payment(double amount, QWidget *parent = nullptr);
    ~Payment();

private slots:
    void on_payButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::Payment *ui;
    double amount;
};

#endif // PAYMENT_H