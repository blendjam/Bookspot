#include "locations.h"
#include "ui_locations.h"

Locations::Locations(QString username, QWidget *parent) : QDialog(parent),
                                                          ui(new Ui::Locations),
                                                          username(username)
{
    ui->setupUi(this);
    if (!userInfo.dbOpen())
    {
        qDebug() << "Failed To connect";
    }
    else
    {
        qDebug() << "Connected";
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT Name FROM Owners");
        if (query.exec())
        {
            model->setQuery(query);
            ui->listView->setModel(model);
        }
        else
        {
            qDebug() << "Error!!";
        }
    }
}

Locations::~Locations()
{
    delete ui;
}

void Locations::on_pushButton_clicked()
{
    auto currentItem = ui->listView->currentIndex();
    int index = currentItem.row();
    QString name = currentItem.data().toString();
    QString ID = name.toLower().split(" ").join("") + QString::number(index);
    QSqlQuery query;
    if (query.exec("SELECT location from Users WHERE username ='" + username + "'"))
    {
        query.next();
        QSqlRecord record = query.record();
        QString location = record.value(0).toString();
        if (location != NULL && location != ID)
        {
            QMessageBox::warning(this, "Already Booked", "You already have booked a spot in another Location");
        }
        else if (index != -1)
        {
            main_window = new MainWindow(username, ID);
            main_window->show();
            this->close();
        }
    }
}
