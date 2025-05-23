#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "flightswindow.h"
#include "hotelswindow.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include "Expedia.hpp"

ManagerWindow::ManagerWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    User *user = GlobalState::getCurrentUser();
    if (user)
        ui->label->setText("Hello, " + QString::fromStdString(user->fullName));

    int flightBookings = 0, hotelBookings = 0;
    double flightRevenue = 0.0, hotelRevenue = 0.0;
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.exec("SELECT COUNT(*) as count, SUM(total_cost) as revenue FROM bookings WHERE flight_id IS NOT NULL AND status = 'Paid'");
        if (query.next())
        {
            flightBookings = query.value("count").toInt();
            flightRevenue = query.value("revenue").toDouble();
        }
        query.exec("SELECT COUNT(*) as count, SUM(total_cost) as revenue FROM bookings WHERE hotel_id IS NOT NULL AND status = 'Paid'");
        if (query.next())
        {
            hotelBookings = query.value("count").toInt();
            hotelRevenue = query.value("revenue").toDouble();
        }
        db.close();
    }

    ui->statsLabel->setText(QString("Flight Bookings: %1\nHotel Bookings: %2\nTotal Revenue: $%3")
                                .arg(flightBookings)
                                .arg(hotelBookings)
                                .arg(flightRevenue + hotelRevenue));
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_flightsButton_clicked()
{
    flightsWindow *flightWin = new flightsWindow(this);
    flightWin->show();
    this->hide();
}

void ManagerWindow::on_hotelsButton_clicked()
{
    HotelsWindow *hotelsWin = new HotelsWindow(this);
    hotelsWin->show();
    this->hide();
}
