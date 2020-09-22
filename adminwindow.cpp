#include "adminwindow.h"
#include "mainwindow.h"
#include "ui_adminwindow.h"
#include "login.h"
#include "locations.h"

AdminWindow::AdminWindow(QString locationID, QString city, QWidget *parent) : QMainWindow(parent),
                                                                              ui(new Ui::AdminWindow), locationID(locationID), city(city)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Locations");
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT fullname, username, type, number, email FROM Users WHERE location = ?");
    query.bindValue(0, locationID);
    if (query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(3, ui->tableView->width() * 0.2);
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
    }
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButton_2_clicked()
{
    if (ui->lineEdit_bike_rate->text() == "" || ui->lineEdit_car_rate->text() == "")
    {
        QMessageBox::information(this, "Empty Fields", "Enter rate of bike and car");
        return;
    }
    int bikeRate = ui->lineEdit_bike_rate->text().toInt();
    int carRate = ui->lineEdit_car_rate->text().toInt();
    QString username = ui->lineEdit->text();
    QSqlQuery qry;
    qry.exec("Select * from Users where username = '" + username + "' AND location = '" + locationID + "'");
    qry.next();
    QSqlRecord record = qry.record();
    int bookStartTime = record.value("start").toInt();
    QString type = record.value("type").toString();
    if (bookStartTime < 1)
    {
        QMessageBox::information(this, "Invalid User", "User hasn't booked");
        return;
    }

    std::time_t bookEndTime = std::time(0);
    auto difference = bookEndTime - bookStartTime;
    int seconds = difference % 60;
    int hours = difference / 60;
    int minutes = hours % 60;
    hours /= 60;
    QString timeString = QString::number(hours) + "hr " + QString::number(minutes) + "min " + QString::number(seconds) + "sec";
    QString money;
    if (type == "car")
    {
        money = QString::number(((hours * 60) + minutes) * carRate);
    }
    else if (type == "bike")
    {
        money = QString::number(((hours * 60) + minutes) * bikeRate);
    }
    QString message = "The parking fee of the user is: Rs " + money;
    QString dialogMessage = "User parked the vehicle for: " + timeString + "\n" + "Do you want to checkout?";
    auto reply = QMessageBox::information(this, "Close Spot", dialogMessage, QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Cost", message);
        QString commandString = "UPDATE Users SET spot= -1, start= -1, location='', city ='', type='' WHERE username = '" + username + "' AND location = '" + locationID + "'";
        QSqlQuery query;
        query.exec(commandString);

        QSqlQueryModel *model = new QSqlQueryModel();
        query.prepare("SELECT fullname, username, type, number , email FROM Users WHERE location = ?");
        query.bindValue(0, locationID);
        if (query.exec())
        {
            model->setQuery(query);
            ui->tableView->setModel(model);
        }
        ui->lineEdit->clear();
    }
}

void AdminWindow::on_pushButton_view_clicked()
{
    MainWindow *w = new MainWindow("**ADMIN**", locationID, city);
    w->show();
}

void AdminWindow::on_pushButton_back_clicked()
{
    auto reply = QMessageBox::information(this, "Confirmation", "Are you sure?", QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Login *loginWindow = new Login();
        loginWindow->show();
        this->close();
    }
}
