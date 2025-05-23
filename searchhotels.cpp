#include "searchhotels.h"
#include "ui_searchhotels.h"

SearchHotels::SearchHotels(QWidget *parent)
    : QDialog(parent), ui(new Ui::SearchHotels)
{
    ui->setupUi(this);
}

SearchHotels::~SearchHotels()
{
    delete ui;
}

void SearchHotels::on_searchButton_clicked()
{
    emit searchRequested(
        ui->cityInput->text(),
        ui->checkInDateInput->date().toString("yyyy-MM-dd"),
        ui->checkOutDateInput->date().toString("yyyy-MM-dd"),
        ui->adultsInput->value(),
        ui->childrenInput->value());
    accept();
}