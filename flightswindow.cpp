#include "flightswindow.h"
#include "ui_flightswindow.h"
#include "searchflights.h"
#include "addflight.h"
#include "managerwindow.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

flightsWindow::flightsWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::flightsWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton, &QPushButton::clicked, this, &flightsWindow::onSearchBtnClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, &flightsWindow::on_backBtn_clicked);
    connect(ui->AddFlight, &QPushButton::clicked, this, &flightsWindow::on_AddFlight_clicked);
}

flightsWindow::~flightsWindow()
{
    delete ui;
}

void flightsWindow::onSearchBtnClicked()
{
    SearchFlights *search = new SearchFlights(this);
    connect(search, &SearchFlights::searchRequested, this, &flightsWindow::performSearch);
    search->exec();
}

void flightsWindow::performSearch(const QString &from, const QString &to, const QString &fromDate, const QString &toDate, int adults, int children)
{
    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database());
    model->setTable("flights");
    QString filter = QString("from_city = '%1' AND to_city = '%2' AND date_time_from LIKE '%3%'").arg(from, to, fromDate);
    model->setFilter(filter);
    model->select();
    ui->tableView->setModel(model);
}

void flightsWindow::on_backBtn_clicked()
{
    ManagerWindow *mainWin = new ManagerWindow(this);
    mainWin->show();
    this->hide();
}

void flightsWindow::on_AddFlight_clicked()
{
    AddFlight *addFlight = new AddFlight(this);
    addFlight->exec();
}