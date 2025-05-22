#include "addflight.h"
#include "ui_addflight.h"

AddFlight::AddFlight(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFlight)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Option 1", 101); // 101 is userData
    ui->comboBox->addItem("Option 2", 101);
}

AddFlight::~AddFlight()
{
    delete ui;
}
