#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "flightswindow.h"
#include "hotelswindow.h"
#include "Expedia.hpp"

ManagerWindow::ManagerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    User *user = GlobalState::getCurrentUser();
    if (user != nullptr)
        ui->welcomeLabel->setText("Welcome, " + QString::fromStdString(user->fullName));
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::on_flightwinBtn_clicked()
{
    this->close();
    flightsWindow *flightwin = new flightsWindow;
    flightwin->show();
}


void ManagerWindow::on_hotelswinBtn_clicked()
{
    this->close();
    HotelsWindow *hotelswin = new HotelsWindow;
    hotelswin->show();
}
