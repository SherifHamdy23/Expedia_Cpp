#include "bookingconfirmation.h"
#include "ui_bookingconfirmation.h"
#include "payment.h"
#include "Expedia.hpp"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

BookingConfirmation::BookingConfirmation(Itinerary *itinerary, QWidget *parent)
    : QDialog(parent), ui(new Ui::BookingConfirmation), itinerary(itinerary)
{
    ui->setupUi(this);
    QString details = QString("Total Cost: $%1").arg(itinerary->getTotalCost());
    ui->detailsLabel->setText(details);
}

BookingConfirmation::~BookingConfirmation()
{
    delete ui;
}

void BookingConfirmation::on_confirmButton_clicked()
{
    Payment *payment = new Payment(itinerary->getTotalCost(), this);
    if (payment->exec() == QDialog::Accepted)
    {
        User *user = GlobalState::getCurrentUser();
        if (user)
        {
            QSqlDatabase db = QSqlDatabase::database();
            if (db.open())
            {
                QSqlQuery query;
                for (const auto &flight : itinerary->flights)
                {
                    query.prepare("INSERT INTO bookings (username, flight_id, total_cost, status) VALUES (:username, :flight_id, :total_cost, 'Paid')");
                    query.bindValue(":username", QString::fromStdString(user->username));
                    query.bindValue(":flight_id", flight->id);
                    query.bindValue(":total_cost", flight->price);
                    query.exec();
                }
                for (const auto &flight : itinerary->turkish_flights)
                {
                    query.prepare("INSERT INTO bookings (username, flight_id, total_cost, status) VALUES (:username, :flight_id, :total_cost, 'Paid')");
                    query.bindValue(":username", QString::fromStdString(user->username));
                    query.bindValue(":flight_id", flight->id);
                    query.bindValue(":total_cost", flight->price);
                    query.exec();
                }
                for (const auto &hotel : itinerary->hotels)
                {
                    query.prepare("INSERT INTO bookings (username, hotel_id, total_cost, status) VALUES (:username, :hotel_id, :total_cost, 'Paid')");
                    query.bindValue(":username", QString::fromStdString(user->username));
                    query.bindValue(":hotel_id", hotel->id);
                    query.bindValue(":total_cost", hotel->price_per_night * hotel->nights);
                    query.exec();
                }
                for (const auto &hotel : itinerary->marriott_rooms)
                {
                    query.prepare("INSERT INTO bookings (username, hotel_id, total_cost, status) VALUES (:username, :hotel_id, :total_cost, 'Paid')");
                    query.bindValue(":username", QString::fromStdString(user->username));
                    query.bindValue(":hotel_id", hotel->id);
                    query.bindValue(":total_cost", hotel->price_per_night * hotel->nights);
                    query.exec();
                }
                db.close();
                QMessageBox::information(this, "Success", "Booking confirmed");
                accept();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to open database");
            }
        }
    }
}

void BookingConfirmation::on_cancelButton_clicked()
{
    reject();
}