#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "signupwindow.h"
#include "managerwindow.h"
#include "CustomerWindow.h"
#include "Expedia.hpp"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_LoginBtn_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Please fill in all fields");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT password, role, fullName FROM users WHERE username = :username");
        query.bindValue(":username", username);
        if (query.exec() && query.next())
        {
            QString storedPassword = query.value("password").toString();
            QString hashedPassword = hashPassword(password);
            if (storedPassword == hashedPassword)
            {
                QString role = query.value("role").toString();
                QString fullName = query.value("fullName").toString();
                GlobalState::setCurrentUser(new User{username.toStdString(), fullName.toStdString(), role.toStdString()});

                if (role == "manager")
                {
                    ManagerWindow *managerWin = new ManagerWindow(this);
                    managerWin->show();
                }
                else
                {
                    CustomerWindow *customerWin = new CustomerWindow(this);
                    customerWin->show();
                }
                this->hide();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Invalid username or password");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Invalid username or password");
        }
        db.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to connect to database");
    }
}

void LoginWindow::on_RegisterBtn_clicked()
{
    signupwindow *signupWin = new signupwindow(this);
    signupWin->show();
    this->hide();
}