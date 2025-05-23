#ifndef SEARCHHOTELS_H
#define SEARCHHOTELS_H

#include <QDialog>

namespace Ui
{
    class SearchHotels;
}

class SearchHotels : public QDialog
{
    Q_OBJECT

public:
    explicit SearchHotels(QWidget *parent = nullptr);
    ~SearchHotels();

signals:
    void searchRequested(const QString &city, const QString &checkInDate, const QString &checkOutDate, int adults, int children);

private slots:
    void on_searchButton_clicked();

private:
    Ui::SearchHotels *ui;
};

#endif // SEARCHHOTELS_H