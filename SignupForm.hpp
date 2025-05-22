#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QMainWindow>
#include "Expedia.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class SignupForm;
}
QT_END_NAMESPACE

class SignupForm : public QMainWindow
{
    Q_OBJECT

public:
    SignupForm(QMainWindow *parent = nullptr);
    ~SignupForm();
    void onSignupClicked();
    void onCancelClicked();

private:
    Ui::SignupForm *ui;
};

#endif // SIGNUPFORM_H
