#include "login.h"
#include "locations.h"
#include "signup.h"
#include "adminwindow.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Bookspot");
    ui->label_3->hide();
}

bool Login::dbOpen()
{
    userInfo = QSqlDatabase::addDatabase("QSQLITE");
    userInfo.setDatabaseName("../Bookspot/database/info.db");
    if (!userInfo.open())
    {
        QMessageBox::warning(this, "404 not found", "Failed to load database");
        return false;
    }
    return true;
}

void Login::dbClose()
{
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QSqlQuery qry;

    QString INPUTusername = ui->lineEdit_username->text();
    QString INPUTpassword = ui->lineEdit_password->text();

    if (!isAdminLogin)
    {

        qry.prepare("select * from Users WHERE username = ? and password = ?");
        qry.bindValue(0, INPUTusername);
        qry.bindValue(1, INPUTpassword);
        if (qry.exec())
        {
            int count = 0;
            while (qry.next())
                count++;

            if (count == 1)
            {
                Locations *location_window = new Locations(INPUTusername);
                location_window->show();
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Wrong Info",
                                     "username or password didn't match");
            }
        }
    }
    else
    {
        qry.prepare("SELECT place, city FROM Admins WHERE username = ? and password = ?");
        qry.bindValue(0, INPUTusername);
        qry.bindValue(1, INPUTpassword);
        if (qry.exec())
        {
            int count = 0;
            QString city, place;
            while (qry.next())
            {
                QSqlRecord record = qry.record();
                place = record.value("place").toString();
                city = record.value("city").toString();
                count++;
            }
            if (count == 1)
            {
                AdminWindow *adminWindow = new AdminWindow(place, city);
                adminWindow->show();
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Wrong Info",
                                     "username or password didn't match");
            }
        }
    }
}

void Login::on_pushButton_2_clicked()
{
    Signup *sign = new Signup;
    sign->show();
    this->close();
}

void Login::on_actionAdmin_triggered()
{
    ui->label_3->show();
    ui->label->hide();
    ui->label_2->hide();
    ui->pushButton->setText("LOGIN");
    ui->pushButton_2->hide();
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    isAdminLogin = true;
}

void Login::on_actionUser_triggered()
{
    ui->label_3->hide();
    ui->label->show();
    ui->label_2->show();
    ui->pushButton->setText("LOGIN");
    ui->pushButton_2->show();
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    isAdminLogin = false;
}
