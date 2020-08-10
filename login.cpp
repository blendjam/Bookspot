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
}

bool Login::dbOpen()
{
    userInfo = QSqlDatabase::addDatabase("QSQLITE");
    // userInfo.setDatabaseName("F:/Qt Projects/Bookspot/Bookspot/database/info.db");
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

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (!isAdminLogin) {
        qry.prepare("select * from Users where username='" + username + "' and password='" + password + "'");

        if (qry.exec())
        {
            int count = 0;
            while (qry.next())
                count++;

            if (count == 1)
            {
                Locations *location_window = new Locations(username);
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
    else {
        qry.prepare("SELECT id, city FROM Admins WHERE username = ? and password = ?");
        qry.bindValue(0, username);
        qry.bindValue(1, password);
        if (qry.exec()) {
            int count = 0;
            QString city, id;
            while (qry.next()) {
                QSqlRecord record = qry.record();
                id = record.value("ID").toString();
                city = record.value("city").toString();
                count++;
            }
            if (count == 1) {
                AdminWindow * adminWindow = new AdminWindow(id, city);
                adminWindow->show();
                this->close();
            }
            else {
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
    ui->loginTitle->setText("Admin Login");
    ui->label->hide();
    ui->pushButton_2->hide();
    isAdminLogin = true;
}
