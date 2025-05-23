#ifndef SEARCHFLIGHTS_H
#define SEARCHFLIGHTS_H

#include <QDialog>

namespace Ui
{
    class SearchFlights;
}

class SearchFlights : public QDialog
{
    Q_OBJECT

public:
    explicit SearchFlights(QWidget *parent = nullptr);
    ~SearchFlights();

signals:
    void searchRequested(const QString &from, const QString &to, const QString &fromDate, const QString &toDate, int adults, int children);

private slots:
    void on_searchButton_clicked();

private:
    Ui::SearchFlights *ui;
};

#endif // SEARCHFLIGHTS_H