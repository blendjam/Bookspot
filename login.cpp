#include "login.h"

#include "ui_login.h"

login::login(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("Bookspot");
}

bool login::dbOpen()
{
    userInfo = QSqlDatabase::addDatabase("QSQLITE");
    userInfo.setDatabaseName("F:/Qt Projects/Bookspot/Bookspot/database/info.db");
    if (!userInfo.open()) {

        QMessageBox::warning(this, "404 not found", "Failed to load database");
        return false;
    }
    return true;
}

void login::dbClose()
{
    userInfo.close();
    userInfo.removeDatabase(QSqlDatabase::defaultConnection);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if (dbOpen()) {
        QSqlQuery qry;
        qry.prepare("select * from main where username='" + username + "' and password='" + password + "'");

        if (qry.exec()) {
            int count = 0;
            while (qry.next())
                count++;

            if (count == 1) {
                MainWindow* main_window = new MainWindow;
                main_window->show();
                this->close();
            } else {
                QMessageBox::warning(this, "Wrong Info",
                    "username or password didn't match");
            }
        }
    }
}