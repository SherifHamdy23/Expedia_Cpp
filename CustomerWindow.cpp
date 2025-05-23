#include "CustomerWindow.h"
#include "ui_CustomerWindow.h"
#include "searchflights.h"
#include "searchhotels.h"
#include "mybookings.h"

CustomerWindow::CustomerWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CustomerWindow)
{
    ui->setupUi(this);
    connect(ui->flightsButton, &QPushButton::clicked, this, &CustomerWindow::on_flightsButton_clicked);
    connect(ui->hotelsButton, &QPushButton::clicked, this, &CustomerWindow::on_hotelsButton_clicked);
    connect(ui->myBookingsButton, &QPushButton::clicked, this, &CustomerWindow::on_myBookingsButton_clicked);
}

CustomerWindow::~CustomerWindow()
{
    delete ui;
}

void CustomerWindow::on_flightsButton_clicked()
{
    SearchFlights *search = new SearchFlights(this);
    search->exec();
}

void CustomerWindow::on_hotelsButton_clicked()
{
    SearchHotels *search = new SearchHotels(this);
    search->exec();
}

void CustomerWindow::on_myBookingsButton_clicked()
{
    MyBookings *bookings = new MyBookings(this);
    bookings->show();
    this->hide();
}