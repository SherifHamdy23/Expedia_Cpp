#include "hotelswindow.h"
#include "ui_hotelswindow.h"
#include "Expedia.hpp"
#include <QTableView>
#include <QStandardItemModel>
#include "mainwindow.h"




HotelsWindow::HotelsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HotelsWindow)
{
    ui->setupUi(this);


    QTableView *tableview = ui->tableView;
    QStandardItemModel *model = new QStandardItemModel(2, 3, tableview);

    // Set headers
    model->setHorizontalHeaderLabels({
        "Hotel Name",
        "room_type",
        "price_per_night",
        "date_from",
        "date_to",
    });

    std::vector<std::string> columns = {
        "Hotel Name",
        "room_type",
        "price_per_night",
        "date_from",
        "date_to",
    };

    // Populate the model with data
    std::vector<HiltonRoom*> Hiltonrooms = HotelAPI::GetHiltonRooms("Alexandria", "2025-9-9", "2025-10-9", 5, 2);
    QStandardItem *item;
    for (size_t row = 0; row < Hiltonrooms.size(); ++row) {
        for (size_t col = 0; col < columns.size(); ++col) {
            if (col == 0) {
                item = new QStandardItem(QString("Hilton"));
            } else if (col == 1) {
                item = new QStandardItem(QString("%1").arg(Hiltonrooms[row]->room_type));
            } else if (col == 2) {
                item = new QStandardItem(QString("%1").arg(Hiltonrooms[row]->price_per_night));
            } else if (col == 3){
                item = new QStandardItem(QString("%1").arg(Hiltonrooms[row]->date_from));
            } else {
                item = new QStandardItem(QString("%1").arg(Hiltonrooms[row]->date_to));
            }
            item->setEditable(false);
            model->setItem(row, col, item);
        }
    }

    std::vector<MarriottRoom*> Marriottrooms = HotelAPI::GetMarriottRooms("Alexandria", "2025-9-9", "2025-10-9", 5, 2);
    size_t actual_row_index = 0;
    for (size_t row = 0; row < Marriottrooms.size(); ++row) {
        actual_row_index = (actual_row_index == 0) ? model->rowCount() + row : actual_row_index + 1;
        for (size_t col = 0; col < columns.size(); ++col) {
            if (col == 0) {
                item = new QStandardItem(QString("Marriott"));
            } else if (col == 1) {
                item = new QStandardItem(QString("%1").arg(Marriottrooms[row]->room_type));
            } else if (col == 2) {
                item = new QStandardItem(QString("%1").arg(Marriottrooms[row]->price_per_night));
            } else if (col == 3){
                item = new QStandardItem(QString("%1").arg(Marriottrooms[row]->date_from));
            } else {
                item = new QStandardItem(QString("%1").arg(Marriottrooms[row]->date_to));
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

HotelsWindow::~HotelsWindow()
{
    delete ui;
}

void HotelsWindow::on_backBtn_clicked()
{
    this->close();
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
}

