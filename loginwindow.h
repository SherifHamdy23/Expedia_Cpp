#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_LoginBtn_clicked();
    void on_RegisterBtn_clicked();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H