#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flightswindow.h"
#include "hotelswindow.h"
#include "Expedia.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    User *user = GlobalState::getCurrentUser();
    if (user != nullptr)
        ui->welcomeLabel->setText("Welcome, " + QString::fromStdString(user->fullName));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_flightwinBtn_clicked()
{
    this->close();
    flightsWindow *flightwin = new flightsWindow;
    flightwin->show();
}


void MainWindow::on_hotelswinBtn_clicked()
{
    this->close();
    HotelsWindow *hotelswin = new HotelsWindow;
    hotelswin->show();
}

