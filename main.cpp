#include <QApplication>
#include "loginwindow.h"
#include "Expedia.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitializeDatabase();
    InitializeUsers();
    LoginWindow w;
    w.show();
    return a.exec();
}
