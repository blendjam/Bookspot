#include "login.h"
#include "locations.h"

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
    userInfo.setDatabaseName("F:/Qt Projects/Bookspot/Bookspot/database/info.db");
    if (!userInfo.open())
    {

        QMessageBox::warning(this, "404 not found", "Failed to load database");
        return false;
    }
    return true;
}

void Login::dbClose()
{
    userInfo.close();
    QSqlDatabase::removeDatabase("QSQLITE");

    return;
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
                Locations *location_window = new Locations(username);
    if(!isRegistering){
        qry.prepare("select * from Users where username='" + username + "' and password='" + password + "'");

        if (qry.exec())
        {
            int count = 0;
            while (qry.next())
                count++;

            if (count == 1)
            {
                location_window->show();
                this->close();
            }
            else
            {
                QMessageBox::warning(this, "Wrong Info",
                                     "username or password didn't match");
            }
        }

    } else {

        QString commandString = "INSERT INTO Users (username, password, spot,start ) VALUES('"+username+"', '"+password+"', -1, -1)";
        if(qry.exec(commandString)){
            QMessageBox::information(this, "Success!!", "You have been successfully registered");
            isRegistering = false;
            ui->pushButton_2->setDisabled(false);
            ui->loginTitle->setText("Login");
            location_window->show();
            this->close();
        } else {

            QMessageBox::warning(this, "Failed!!", "Something went wrong");
        }
    }
}

void Login::on_pushButton_2_clicked()
{
   ui->loginTitle->setText("Register");
   ui->pushButton_2->setDisabled(true);
    isRegistering = true;
}
