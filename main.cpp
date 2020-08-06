#include "login.h"
#include "mainwindow.h"
#include "locations.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.dbOpen();
    // MainWindow w("sanket");
    w.show();
    return a.exec();
}
