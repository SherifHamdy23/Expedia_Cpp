#ifndef ADDFLIGHT_H
#define ADDFLIGHT_H

#include <QDialog>

namespace Ui
{
    class AddFlight;
}

class AddFlight : public QDialog
{
    Q_OBJECT

public:
    explicit AddFlight(QWidget *parent = nullptr);
    ~AddFlight();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AddFlight *ui;
};

#endif // ADDFLIGHT_H