#include "SignupForm.hpp"
#include "ui_SignupForm.h"
#include <QString>
#include <QMessageBox>
#include <QDebug> // For printing values to console

SignupForm::SignupForm(QMainWindow* parent) :QMainWindow(parent), ui(new Ui::SignupForm)
{
    ui->setupUi(this);
    connect(ui->btnSignup, &QPushButton::clicked, this, &SignupForm::onSignupClicked);
}


SignupForm::~SignupForm() {
        delete ui;
}

void SignupForm::onSignupClicked() {
    qDebug() << "Signup Btn Clicked";
    return;
    std::string username = this->ui->txtUsername->text().toStdString();
    std::string password = this->ui->txtPassword->text().toStdString();
    std::string fullName = this->ui->txtFullName->text().toStdString();

    if (GlobalState::Users.find(username) == GlobalState::Users.end()) {
        GlobalState::Users[username] = new User(username, password, fullName);
        QMessageBox::information(this, "Success", "Sign up successful");
        close();
    } else {
        QMessageBox::critical(this, "Error", "Username already exists");
    }
}

void SignupForm::onCancelClicked() {
    close();
}
