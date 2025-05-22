#include "loginwindow.h"
#include "signupwindow.h"
#include "ui_loginwindow.h"
#include "hotelswindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <iostream>
#include "Expedia.hpp"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::on_RegisterBtn_clicked()
{
    qDebug() << "Register Btn Clicked";
    signupwindow *form = new signupwindow(); // Allocate on heap
    form->show();
    this->close();

}


void LoginWindow::on_LoginBtn_clicked()
{
    std::map<std::string, User*> users = GlobalState::Users;
    std::string username = ui->usernameInput->text().toStdString();
    std::string passwd = ui->passwordInput->text().toStdString();
    auto search = users.find(username);
    if (search != users.end()) {
        std::cout << username << " found in users" << std::endl;
        User *user = users[username];
        if (user->password == passwd) {
            std::cout << "password matched" << std::endl;
            GlobalState::setCurrentUser(user);
            this->close();
            MainWindow *form = new MainWindow;
            form->show();

        }
    } else
        std:: cout << username << " not found in users" << std::endl;

    User *user = GlobalState::getCurrentUser();
    if (user != nullptr)
        qDebug() << "user is set";
    qDebug() << "you clicked Login Btn";

}

