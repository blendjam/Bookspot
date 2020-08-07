#include "locations.h"
#include "ui_locations.h"
#include "login.h"

Locations::Locations(QString username, QWidget *parent) : QDialog(parent),
ui(new Ui::Locations),
username(username)
{
    ui->setupUi(this);
    QSqlQuery query;
    query.prepare("SELECT City FROM Cities");
    if (query.exec()) {
        while (query.next()) {
            QSqlRecord record = query.record();
            QString city = record.value(0).toString();
            ui->comboBox_city->addItem(city);
        }
    }

    else
    {
        qDebug() << "Error!!";
    }
}

Locations::~Locations()
{
    delete ui;
}

void Locations::on_pushButton_clicked()
{
    auto currentItem = ui->tableView->currentIndex();
    int index = currentItem.row();

    QString name = currentItem.data().toString();
    QString locationID = name.toLower().split(" ").join("") + QString::number(index);
    QSqlQuery query;
    if (query.exec("SELECT location, city FROM Users WHERE username ='" + username + "'"))
    {
        query.next();
        QSqlRecord record = query.record();
        QString location = record.value("location").toString();
        QString city = record.value("city").toString();

        if (location != "" && city != "" && location != locationID)
        {
            QMessageBox::warning(this, "Already Booked", "You already have booked a spot in another Location");
        }
        else if (index != -1)
        {
            main_window = new MainWindow(username, locationID, currentCity);
            main_window->show();
            this->close();
        }
    }
}

void Locations::on_pushButton_2_clicked()
{
    Login* loginWindow = new Login();
    loginWindow->show();
    this->close();
}


void Locations::on_comboBox_city_currentIndexChanged(const QString &City)
{
    currentCity = City;
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT Name, Location FROM " + City);
    if (query.exec()) {
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0, ui->tableView->width() - ui->tableView->columnWidth(1));
    }

}
