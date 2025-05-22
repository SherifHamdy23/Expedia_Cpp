#include "CustomerWindow.h"
#include "ui_CustomerWindow.h"
#include "flightswindow.h"
#include "hotelswindow.h"
#include "Expedia.hpp"

CustomerWindow::CustomerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CustomerWindow)
{
    ui->setupUi(this);

    User *user = GlobalState::getCurrentUser();
    if (user != nullptr)
        ui->welcomeLabel->setText("Welcome, " + QString::fromStdString(user->fullName));

}

CustomerWindow::~CustomerWindow()
{
    delete ui;
}

void CustomerWindow::on_flightwinBtn_clicked()
{
    this->close();
    flightsWindow *flightwin = new flightsWindow;
    flightwin->show();
}


void CustomerWindow::on_hotelswinBtn_clicked()
{
    this->close();
    HotelsWindow *hotelswin = new HotelsWindow;
    hotelswin->show();
}

