#include "editflight.h"
#include "ui_editflight.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

EditFlight::EditFlight(int flightId, QWidget *parent)
    : QDialog(parent), ui(new Ui::EditFlight), flightId(flightId)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query;
        query.prepare("SELECT airline, departureCity, arrivalCity, departureDate, returnDate, price FROM flights WHERE id = :id");
        query.bindValue(":id", flightId);
        if (query.exec() && query.next())
        {
            ui->airlineInput->setCurrentText(query.value("airline").toString());
            ui->fromInput->setText(query.value("departureCity").toString());
            ui->toInput->setText(query.value("arrivalCity").toString());
            ui->departureDateInput->setDate(QDate::fromString(query.value("departureDate").toString(), "yyyy-MM-dd"));
            ui->returnDateInput->setDate(QDate::fromString(query.value("returnDate").toString(), "yyyy-MM-dd"));
            ui->priceInput->setValue(query.value("price").toDouble());
        }
        db.close();
    }
}

EditFlight::~EditFlight()
{
    delete ui;
}

void EditFlight::on_buttonBox_accepted()
{
    QString from = ui->fromInput->text();
    QString to = ui->toInput->text();
    double price = ui->priceInput->value();
    QString departureDate = ui->departureDateInput->date().toString("yyyy-MM-dd");
    QString returnDate = ui->returnDateInput->date().toString("yyyy-MM-dd");
    QString airline = ui->airlineInput->currentText();

    if (from.isEmpty() || to.isEmpty() || price <= 0.0)
    {
        QMessageBox::critical(this, "Error", "All fields are required and price must be greater than 0");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query;
        query.prepare("UPDATE flights SET airline = :airline, departureCity = :from, arrivalCity = :to, "
                      "departureDate = :departureDate, returnDate = :returnDate, price = :price WHERE id = :id");
        query.bindValue(":airline", airline);
        query.bindValue(":from", from);
        query.bindValue(":to", to);
        query.bindValue(":departureDate", departureDate);
        query.bindValue(":returnDate", returnDate);
        query.bindValue(":price", price);
        query.bindValue(":id", flightId);
        if (query.exec())
        {
            QMessageBox::information(this, "Success", "Flight updated successfully");
            accept();
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to update flight");
        }
        db.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open database");
    }
}

void EditFlight::on_buttonBox_rejected()
{
    reject();
}