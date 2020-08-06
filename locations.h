#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
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

    void on_pushButton_2_clicked();

    void on_comboBox_city_currentIndexChanged(const QString &arg1);

private:
    Ui::Locations *ui;
    MainWindow *main_window;
    QString username;
    QString currentCity;
};

#endif // LOCATIONS_H
