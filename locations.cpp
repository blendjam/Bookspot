#include "locations.h"
#include "ui_locations.h"
#include "login.h"

Locations::Locations(QString username, QWidget *parent) : QDialog(parent),
                                                          ui(new Ui::Locations),
                                                          username(username)
{
    ui->setupUi(this);
    this->setWindowTitle("Locations");
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(handleDoubleClicked(const QModelIndex &)));
    QSqlQuery query;
    query.prepare("SELECT City FROM Cities");
    if (query.exec())
    {
        while (query.next())
        {
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

void Locations::handleDoubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        auto currentItem = ui->tableView->currentIndex();
        QString locationID = currentItem.data().toString();
        QString vehicleType = ui->comboBox_type->currentText();
        QSqlQuery query;
        query.prepare("SELECT * FROM Users WHERE username = ?");
        query.bindValue(0, username);

        if (query.exec())
        {
            query.next();
            QSqlRecord record = query.record();
            QString location = record.value("location").toString();
            QString city = record.value("city").toString();

            if ((city == currentCity && location == locationID) || (city == "" && location == ""))
            {
                main_window = new MainWindow(username, locationID, currentCity, vehicleType);
                main_window->show();
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Already Booked", "You already have booked a spot at " + location + ", " + city);
                return;
            }
        }
    }
    else
    {
        QMessageBox::information(this, "Invalid Column", "Double Click the name of the parking spot");
    }
}

Locations::~Locations()
{
    delete ui;
}

void Locations::on_pushButton_clicked()
{
    auto currentItem = ui->tableView->currentIndex();
    if (currentItem.column() == 0)
    {
        handleDoubleClicked(currentItem);
    }
    else
    {
        QMessageBox::information(this, "Invalid Column", "Select the name of the parking spot");
    }
}

void Locations::on_pushButton_2_clicked()
{
    auto reply = QMessageBox::information(this, "Confirmation", "Are you sure?", QMessageBox::Yes, QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        Login *loginWindow = new Login();
        loginWindow->show();
        this->close();
    }
}

void Locations::on_comboBox_city_currentIndexChanged(const QString &City)
{
    currentCity = City;
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT Name, Location FROM " + City);
    if (query.exec())
    {
        model->setQuery(query);
        ui->tableView->setModel(model);
        ui->tableView->setColumnWidth(0, ui->tableView->width() - ui->tableView->columnWidth(1) - 50);
    }
}
