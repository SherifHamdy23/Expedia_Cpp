#include "mybookings.h"
#include "ui_mybookings.h"
#include "CustomerWindow.h"
#include "Expedia.hpp"
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QSqlDatabase>

MyBookings::MyBookings(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MyBookings)
{
    ui->setupUi(this);
    User *user = GlobalState::getCurrentUser();
    if (!user)
        return;

    QTableView *tableview = ui->tableView;
    QStandardItemModel *model = new QStandardItemModel(0, 4, tableview);
    model->setHorizontalHeaderLabels({"Type", "Details", "Total Cost", "Status"});
    tableview->setModel(model);
    tableview->setSelectionMode(QAbstractItemView::SingleSelection);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableview->horizontalHeader()->setStretchLastSection(true);

    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT flight_id, hotel_id, total_cost, status FROM bookings WHERE username = :username");
        query.bindValue(":username", QString::fromStdString(user->username));
        if (query.exec())
        {
            int row = 0;
            while (query.next())
            {
                model->insertRow(row);
                QString type = query.value("flight_id").isNull() ? "Hotel" : "Flight";
                QString details = query.value("flight_id").isNull() ? QString("Hotel ID: %1").arg(query.value("hotel_id").toInt()) : QString("Flight ID: %1").arg(query.value("flight_id").toInt());
                model->setItem(row, 0, new QStandardItem(type));
                model->setItem(row, 1, new QStandardItem(details));
                model->setItem(row, 2, new QStandardItem(QString::number(query.value("total_cost").toDouble())));
                model->setItem(row, 3, new QStandardItem(query.value("status").toString()));
                row++;
            }
        }
        db.close();
    }
}

MyBookings::~MyBookings()
{
    delete ui;
}

void MyBookings::on_backButton_clicked()
{
    CustomerWindow *mainWin = new CustomerWindow(this);
    mainWin->show();
    this->hide();
}