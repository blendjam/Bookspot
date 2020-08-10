#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QMessageBox>
#include <QValidator>

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

void Signup::on_pushButton_clicked()
{
    Signup sign;
    QString fullname, username, password, confirm_pw, gmail, address, number;
    fullname = ui->lineEdit->text();
    username = ui->lineEdit_2->text();
    password = ui->lineEdit_3->text();
    confirm_pw = ui->lineEdit_4->text();
    gmail = ui->lineEdit_5->text();
    number = ui->lineEdit_6->text();
    address = ui->lineEdit_7->text();

    if (confirm_pw != password)
    {
        QMessageBox::warning(this, "Error", "Passwords don't match");
    }

    else
    {
        QSqlQuery qry;
        int count = 0;
        if (qry.exec("SELECT * from Users where username = '" + username + "'")) {
            while (qry.next()) {
                count++;
            }
            if (count == 1) {
                QMessageBox::information(this, "Duplicate", "Username already exists. Plese Select a unique username");
            }
            else {
                qry.prepare("insert into Users (fullname, username, password, gmail, number, address, spot, start) values('"+fullname+"', '"+username+"', '"+password+"', '"+gmail+"', '"+number+"', '"+address+"', -1, -1)");
                if (qry.exec())
                {
                    QMessageBox::information(this, "Success", "You have successfully signed up");
                    Login *login = new Login;
                    login->show();
                    this->close();
                }
                else {
                    QMessageBox::information(this, "Information", "Failed to load data"), qry.lastError().text();
                }

            }
        }
        else {
            QMessageBox::information(this, "Information", "Failed to load data");
        }
    }
}

void Signup::on_pushButton_2_clicked()
{
    Login *login = new Login;
    login->show();
    this->close();
}
