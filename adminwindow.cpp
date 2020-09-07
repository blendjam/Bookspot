#include "adminwindow.h"
#include "mainwindow.h"
#include "ui_adminwindow.h"
#include "login.h"

AdminWindow::AdminWindow(QString locationID, QString city, QWidget *parent) : QMainWindow(parent), ui(new Ui::AdminWindow), locationID(locationID), city(city)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Window");

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT fullname, username, number, address, gmail FROM Users WHERE location = ?");
    query.bindValue(0, locationID);
    if (query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButton_2_clicked()
{
    QString username = ui->lineEdit->text();
    QSqlQuery qry;
    qry.exec("Select * from Users where username = '" + username + "' AND location = '" + locationID + "'");
    qry.next();
    QSqlRecord record = qry.record();
    int bookStartTime = record.value("start").toInt();
    qDebug() << bookStartTime;
    if (bookStartTime < 1)
    {

        QMessageBox::information(this, "Title", "User hasn't booked");
        return;
    }

    std::time_t bookEndTime = std::time(0);
    auto difference = bookEndTime - bookStartTime;
    int seconds = difference % 60;
    int hours = difference / 60;
    int minutes = hours % 60;
    hours /= 60;
    QString timeString = QString::number(hours) + "hr " + QString::number(minutes) + "min " + QString::number(seconds) + "sec";
    QString money = QString::number(((hours * 60) + minutes) * 1);
    QString message = "The parking fee of the user is: Rs " + money;
    QString dialogMessage = "User parked the vehicle for: " + timeString + "\n"
                                                                           "Do you want to checkout?";
    auto reply = QMessageBox::information(this, "Close Spot", dialogMessage, QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Cost", message);
        QString commandString = "UPDATE Users SET spot= -1, start= -1, location='', city ='' WHERE username = '" + username + "' AND location = '" + locationID + "'";
        QSqlQuery query;
        query.exec(commandString);

        QSqlQueryModel *model = new QSqlQueryModel();
        query.prepare("SELECT fullname, username, number, address, gmail FROM Users WHERE location = ?");
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
    MainWindow *w = new MainWindow("ADMINADMIN", locationID, city);
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
