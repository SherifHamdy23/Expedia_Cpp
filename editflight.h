#ifndef EDITFLIGHT_H
#define EDITFLIGHT_H

#include <QDialog>

namespace Ui
{
    class EditFlight;
}

class EditFlight : public QDialog
{
    Q_OBJECT

public:
    explicit EditFlight(int flightId, QWidget *parent = nullptr);
    ~EditFlight();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::EditFlight *ui;
    int flightId;
};

#endif