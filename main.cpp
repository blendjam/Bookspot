#include "login.h"
#include "mainwindow.h"
#include "locations.h"
#include "adminwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.dbOpen();
    // AdminWindow w("bhatmall0", "Kathmandu");
    w.show();

    return a.exec();
}
