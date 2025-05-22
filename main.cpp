#include "mainwindow.h"
#include "Expedia.hpp"
#include "loginwindow.h"
#include "flightswindow.h"
#include "hotelswindow.h"
#include <iostream>
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow form;
    InitializeUsers();
    form.show();
    auto flights = AirCanadaAPI::GetFlights("NYC", "LAX", "25-01-22", "10-02-22", 2, 1);
    for (const auto* flight : flights) {
        std::cout << "Price: " << flight->price << ", From: " << flight->date_time_from << std::endl;
    }
    // w.show();
    return a.exec();
}
