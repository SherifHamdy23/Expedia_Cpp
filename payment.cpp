#include "payment.h"
#include "ui_payment.h"
#include "Expedia.hpp"
#include <QMessageBox>

Payment::Payment(double amount, QWidget *parent)
    : QDialog(parent), ui(new Ui::Payment), amount(amount)
{
    ui->setupUi(this);
}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_payButton_clicked()
{
    QString cardNumber = ui->cardNumberInput->text();
    QString expiryDate = ui->expiryDateInput->text();
    QString cvv = ui->cvvInput->text();

    if (cardNumber.isEmpty() || expiryDate.isEmpty() || cvv.isEmpty())
    {
        QMessageBox::critical(this, "Error", "All fields are required");
        return;
    }

    User *user = GlobalState::getCurrentUser();
    if (!user)
    {
        QMessageBox::critical(this, "Error", "No user logged in");
        return;
    }

    if (StripeAPI::WithdrawMoney(user->username, cardNumber.toStdString(), amount))
    {
        QMessageBox::information(this, "Success", "Payment successful");
        accept();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Payment failed");
    }
}

void Payment::on_cancelButton_clicked()
{
    reject();
}