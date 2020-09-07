#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QMessageBox>
#include <map>
#include <QValidator>

Signup::Signup(QWidget *parent) : QDialog(parent),
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
    gmail = ui->lineEdit_5->text();
    number = ui->lineEdit_6->text();
    address = ui->lineEdit_7->text();
    confirm_pw = ui->lineEdit_4->text();
    if(fullname.length() == 0 || username.length() == 0 || password.length() == 0
       || gmail.length() == 0 || number.length() == 0 || address.length() == 0 || confirm_pw.length() == 0)
    {

        QMessageBox::warning(this, "Empty", "Please fill all the fileds");
        return;
    }
    bool test;
    number.toInt(&test, 10);
    if (!test)
    {
        QMessageBox::warning(this, "Not a Number", "Please Enter a valid number");
        return;
    }
    if(password != confirm_pw)
    {
        QMessageBox::warning(this, "Invalid Password", "Password and Confirm Password didn't match");
        return;
    }
    if (number.length() != 10)
    {
        QMessageBox::warning(this, "Number Length", "Please Enter a number of size 10");
        return;
    }

    if (!(gmail.contains("@") && gmail.contains(".com")))
    {
        QMessageBox::warning(this, "Error", "Please enter valid email format");
        return;
    }

    QSqlQuery qry;
    int count = 0;
    if (qry.exec("SELECT * from Users where username = '" + username + "'"))
    {
        while (qry.next())
        {
            count++;
        }
        if (count == 1)
        {
            QMessageBox::information(this, "Duplicate", "Username already exists. Plese Select a unique username");
        }
        else
        {
            qry.prepare("insert into Users (fullname, username, password, gmail, number, address, spot, start) values('" + fullname + "', '" + username + "', '" + password + "', '" + gmail + "', '" + number + "', '" + address + "', -1, -1)");
            if (qry.exec())
            {
                QMessageBox::information(this, "Success", "You have successfully signed up");
                Login *login = new Login;
                login->show();
                this->close();
            }
            else
            {
                QMessageBox::information(this, "Information", "Failed to load data"), qry.lastError().text();
            }
        }
    }
    else
    {
        QMessageBox::information(this, "Information", "Failed to load data");
    }
}

void Signup::on_pushButton_2_clicked()
{
    Login *login = new Login;
    login->show();
    this->close();
}

void Signup::on_lineEdit_3_textEdited(const QString &arg1)
{
    QString color ;
    if (arg1.length() < 5)
    {
        color ="red";
    }
    else if (arg1.length() < 8)
    {
        color = "orange";
    }
    else if(arg1.length() < 12)
    {
        color = "yellow";
    } else if(arg1.length() <= 15)
    {
        color = "green";
    }
    else
    {
        QMessageBox::warning(this, "Error!", "Password must be less than 16 characters");
        ui->lineEdit_3->backspace();
    }

    ui->lineEdit_3->setStyleSheet("color: " + color);
}
