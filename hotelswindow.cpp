#include "hotelswindow.h"
#include "ui_hotelswindow.h"
#include "searchhotels.h"
#include "managerwindow.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

HotelsWindow::HotelsWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::HotelsWindow)
{
    ui->setupUi(this);
    connect(ui->searchButton, &QPushButton::clicked, this, &HotelsWindow::onSearchBtnClicked);
    connect(ui->backButton, &QPushButton::clicked, this, &HotelsWindow::on_backButton_clicked);
}

HotelsWindow::~HotelsWindow()
{
    delete ui;
}

void HotelsWindow::onSearchBtnClicked()
{
    SearchHotels *search = new SearchHotels(this);
    connect(search, &SearchHotels::searchRequested, this, &HotelsWindow::performSearch);
    search->exec();
}

void HotelsWindow::performSearch(const QString &city, const QString &checkInDate, const QString &checkOutDate, int adults, int children)
{
    QSqlTableModel *model = new QSqlTableModel(this, QSqlDatabase::database());
    model->setTable("hotels");
    QString filter = QString("city = '%1' AND date_from LIKE '%2%'").arg(city, checkInDate);
    model->setFilter(filter);
    model->select();
    ui->tableView->setModel(model);
}

void HotelsWindow::on_backButton_clicked()
{
    ManagerWindow *mainWin = new ManagerWindow(this);
    mainWin->show();
    this->hide();
}