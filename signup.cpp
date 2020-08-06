#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QMessageBox>

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

bool Signup::dbOpen()
{
    userinfo = QSqlDatabase::addDatabase("QSQLITE");
    userinfo.setDatabaseName("D:/qt_workspace/Bookspot/database/info.db");
    if (!userinfo.open())
    {
        QMessageBox::warning(this, "404 not found", "Failed to load database");
        return false;
    }
    return true;
}

void Signup::dbClose()
{
    userinfo.close();
    QSqlDatabase::removeDatabase("QSQLITE");
    return;
}

void Signup::on_pushButton_clicked()
{
    Signup sign;
    QString fullname, username, password, gmail, address, number;
    fullname = ui->lineEdit->text();
    username = ui->lineEdit_2->text();
    password = ui->lineEdit_3->text();
    gmail = ui->lineEdit_5->text();
    number = ui->lineEdit_6->text();
    address = ui->lineEdit_7->text();

    if(!sign.dbOpen())
        {
            QMessageBox::warning(this, "404 not found", "Failed to load database");
    }

    if (sign.dbOpen())
    {
        QSqlQuery qry;
        qry.prepare("insert into Users (fullname, username, password, gmail, number, address, spot, start) values('"+fullname+"', '"+username+"', '"+password+"', '"+gmail+"', '"+number+"', '"+address+"', -1, -1)");

        if (qry.exec())
        {
            auto reply= QMessageBox::information(this, "Confirmation", "Do you confirm that the data you provided is correct?", QMessageBox:: Yes, QMessageBox:: No);
            if(reply == QMessageBox:: Yes){
                QMessageBox::information(this, "Success", "You have successfully signed up");
                sign.dbClose();
                Login *login = new Login;
                login->show();
                this->close();
            }

        }
        else{
            QMessageBox::information(this, "Information", "Error"), qry.lastError().text();
        }
    }



}
