#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include <QMessageBox>
#include <QValidator>

Signup::Signup(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Signup)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 12);
    ui->progressBar->setValue(0);
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
    bool test;
    number.toInt(&test, 10);
    if (!test)
    {
        QMessageBox::warning(this, "Not a Number", "Please Enter a valid number");
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
    ui->progressBar->setValue(arg1.length());
    QString color = "red";
    if (arg1.length() < 5)
    {
        ui->label_strength->setText("Weak");
    }
    else if (arg1.length() < 8)
    {
        color = "orange";
        ui->label_strength->setText("Medium");
    }
    else
    {
        color = "#43f030";
        ui->label_strength->setText("Strong");
    }
    ui->progressBar->setStyleSheet(" QProgressBar::chunk {background-color: " + color + "}");
}
