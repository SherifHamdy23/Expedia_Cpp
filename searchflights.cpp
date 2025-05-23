#include "searchflights.h"
#include "ui_searchflights.h"

SearchFlights::SearchFlights(QWidget *parent)
    : QDialog(parent), ui(new Ui::SearchFlights)
{
    ui->setupUi(this);
}

SearchFlights::~SearchFlights()
{
    delete ui;
}

void SearchFlights::on_searchButton_clicked()
{
    emit searchRequested(
        ui->fromInput->text(),
        ui->toInput->text(),
        ui->departureDateInput->date().toString("yyyy-MM-dd"),
        ui->returnDateInput->date().toString("yyyy-MM-dd"),
        ui->adultsInput->value(),
        ui->childrenInput->value());
    accept();
}