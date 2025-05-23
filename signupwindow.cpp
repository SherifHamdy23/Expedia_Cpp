#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "loginwindow.h"
#include "Expedia.hpp"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>


signupwindow::signupwindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::signupwindow)
{
    ui->setupUi(this);
}

signupwindow::~signupwindow()
{
    delete ui;
}

void signupwindow::on_RegisterBtn_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    QString confirmPassword = ui->confirmPasswordInput->text();
    QString fullName = ui->fullNameInput->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty() || fullName.isEmpty())
    {
        QMessageBox::critical(this, "Error", "All fields are required");
        return;
    }

    if (password != confirmPassword)
    {
        QMessageBox::critical(this, "Error", "Passwords do not match");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT username FROM users WHERE username = :username");
        query.bindValue(":username", username);
        if (query.exec() && query.next())
        {
            QMessageBox::critical(this, "Error", "Username already exists");
            db.close();
            return;
        }

        query.prepare("INSERT INTO users (username, password, fullName, role) VALUES (:username, :password, :fullName, :role)");
        query.bindValue(":username", username);
        query.bindValue(":password", hashPassword(password));
        query.bindValue(":fullName", fullName);
        query.bindValue(":role", "customer");
        if (query.exec())
        {
            QMessageBox::information(this, "Success", "Sign up successful");
            this->hide();
            LoginWindow *loginWin = new LoginWindow(this);
            loginWin->show();
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to sign up: " + query.lastError().text());
        }
        db.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open database");
    }
}

void signupwindow::on_LoginBtn_clicked()
{
    LoginWindow *loginWin = new LoginWindow(this);
    loginWin->show();
    this->hide();
}
