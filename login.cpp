#include "login.h"

#include "ui_login.h"

login::login(QWidget *parent) : QMainWindow(parent), ui(new Ui::login) {
  ui->setupUi(this);
}

login::~login() { delete ui; }

void login::on_pushButton_clicked() {
  QString password = ui->lineEdit_password->text();
  QString username = ui->lineEdit_username->text();

  // Check for username and password
  if (password == QString("bookspot") && username == QString("bookspot")) {
    main_window.show();
    this->close();

  } else {
    QMessageBox::warning(this, "Wrong Info",
                         "username or password didn't match");
  }
}