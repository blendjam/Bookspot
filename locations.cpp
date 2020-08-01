#include "locations.h"
#include "ui_locations.h"

Locations::Locations(QWidget *parent) : QDialog(parent),
                                        ui(new Ui::Locations)
{
    ui->setupUi(this);
    if (!loginDialog.dbOpen())
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
    if (index != -1)
    {
        loginDialog.setTableName(name, index);
        loginDialog.show();
        this->close();
    }
}
