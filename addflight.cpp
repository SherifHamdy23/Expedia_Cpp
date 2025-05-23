#include "addflight.h"
#include "ui_addflight.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>


AddFlight::AddFlight(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddFlight)
{
    ui->setupUi(this);
}

AddFlight::~AddFlight()
{
    delete ui;
}

void AddFlight::on_buttonBox_accepted()
{
    QString from = ui->fromInput->text();
    QString to = ui->toInput->text();
    double price = ui->priceInput->value();
    QString departureDate = ui->departureDateInput->date().toString("yyyy-MM-dd");
    QString returnDate = ui->returnDateInput->date().toString("yyyy-MM-dd");
    QString airline = ui->airlineCombo->currentText();

    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO flights (airline, from_city, to_city, date_time_from, date_time_to, price) "
                      "VALUES (:airline, :from, :to, :fromDate, :toDate, :price)");
        query.bindValue(":airline", airline);
        query.bindValue(":from", from);
        query.bindValue(":to", to);
        query.bindValue(":fromDate", departureDate);
        query.bindValue(":toDate", returnDate);
        query.bindValue(":price", price);
        if (query.exec())
        {
            QMessageBox::information(this, "Success", "Flight added successfully");
            accept();
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to add flight: " + query.lastError().text());
        }
        db.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open database");
    }
}

void AddFlight::on_buttonBox_rejected()
{
    reject();
}
