#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QMainWindow>

namespace Ui {
class signupwindow;
}

class signupwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit signupwindow(QWidget *parent = nullptr);
    ~signupwindow();

private slots:
    void on_RegisterBtn_clicked();
    void on_LoginBtn_clicked();

private:
    Ui::signupwindow *ui;
};

#endif // SIGNUPWINDOW_H
