#include "flightswindow.h"
#include "ui_flightswindow.h"
#include "Expedia.hpp"
#include <QTableView>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "addflight.h"

std::map<int, std::string> columns = {
    {0, "Airline"},
    {1, "date_time_from"},
    {2, "data_time_to"},
    {3, "Price"},
};

flightsWindow::flightsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::flightsWindow)
{
    ui->setupUi(this);

    QTableView *tableview = ui->tableView;
    QStandardItemModel *model = new QStandardItemModel(4, 3, tableview);

    // Set headers
    model->setHorizontalHeaderLabels({"Airline", "Price", "date_time_from", "data_time_to"});


    std::string from = "New York";
    std::string to = "London";
    std::string fromDate = "2025-06-01";
    std::string toDate = "2025-06-15";
    int adults = 2;
    int children = 1;
    // Populate the model with data
    std::vector<AirCanadaFlight*> flights = AirCanadaAPI::GetFlights(from, to, fromDate, toDate, adults, children);
    QStandardItem *item;

    for (size_t row = 0; row < flights.size(); ++row) {
        for (size_t col = 0; col < columns.size(); ++col) {
            if (col == 0) {
                item = new QStandardItem(QString("AirCanada"));
            } else if (col == 1) {
                item = new QStandardItem(QString("%1").arg(flights[row]->price));
            } else if (col == 2) {
                item = new QStandardItem(QString("%1").arg(flights[row]->date_time_from));
            } else {
                item = new QStandardItem(QString("%1").arg(flights[row]->date_time_from));
            }
           item->setEditable(false);
           model->setItem(row, col, item);
        }
    }

    std::vector<TurkishFlight*> Turkishflights = TurkishAirlinesAPI::GetFlights(from, to, fromDate, toDate, adults, children, 2);
    size_t actual_row_index = 0;
    for (size_t row = 0; row < Turkishflights.size(); ++row) {
        actual_row_index = (actual_row_index == 0) ? model->rowCount() + row : actual_row_index + 1;
        for (size_t col = 0; col < columns.size(); ++col) {
            if (col == 0) {
                item = new QStandardItem(QString("Turkish Airline"));
            } else if (col == 1) {
                item = new QStandardItem(QString("%1").arg(Turkishflights[row]->price));
            } else if (col == 2) {
                item = new QStandardItem(QString("%1").arg(Turkishflights[row]->date_time_from));
            } else {
                item = new QStandardItem(QString("%1").arg(Turkishflights[row]->date_time_from));
            }
           item->setEditable(false);
            model->setItem(actual_row_index, col, item);
        }
    }

    // Connect the model to the table view
    tableview->setModel(model);
    tableview->setSelectionMode(QAbstractItemView::SingleSelection);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview->horizontalHeader()->setStretchLastSection(true);
}

flightsWindow::~flightsWindow()
{
    delete ui;
}

void flightsWindow::on_backBtn_clicked()
{
    this->close();
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
}


void flightsWindow::on_pushButton_clicked()
{
    AddFlight *addFlight = new AddFlight;
    addFlight->show();
}

