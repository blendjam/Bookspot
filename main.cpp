#include "login.h"
#include "mainwindow.h"
#include "locations.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //     Login w;
    // MainWindow w("sanket");
    Locations w;
    w.show();
    return a.exec();
}
