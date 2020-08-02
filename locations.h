#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include "mainwindow.h"

namespace Ui
{
    class Locations;
}

class Locations : public QDialog
{
    Q_OBJECT

public:
    explicit Locations(QString username, QWidget *parent = nullptr);
    ~Locations();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Locations *ui;
    MainWindow *main_window;
    QString username;
    Login userInfo;
};

#endif // LOCATIONS_H
