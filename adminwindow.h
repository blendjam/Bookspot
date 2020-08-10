#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlRecord>
#include <ctime>


namespace Ui {
    class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QString locationID, QString city, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_view_clicked();

private:
    Ui::AdminWindow *ui;
    QString locationID;
    QString city;
};

#endif // ADMINWINDOW_H
