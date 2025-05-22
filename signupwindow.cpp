#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "loginwindow.h"
#include "Expedia.hpp"
#include <QDebug>

signupwindow::signupwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signupwindow)
{
    ui->setupUi(this);
}

signupwindow::~signupwindow()
{
    delete ui;
}

void signupwindow::on_RegisterBtn_clicked()
{
    qDebug() << "Register Btn Clicked";

}

void signupwindow::on_LoginBtn_clicked()
{
    qDebug() << "Register Btn Clicked";
    LoginWindow *form = new LoginWindow(); // Allocate on heap
    this->hide();
    form->show();

}

