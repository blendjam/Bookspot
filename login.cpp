#include "login.h"

#include "ui_login.h"

login::login(QWidget *parent) : QMainWindow(parent), ui(new Ui::login) {
  ui->setupUi(this);
}

login::~login() { delete ui; }

void login::on_pushButton_clicked() {
  // Check for username and password
  if (password == QString("bookspot") && username == QString("bookspot")) {
    main_window.centralWidget();
    main_window.raise();
    main_window.show();
    this->close();

  } else {
    // show dialog
    QMessageBox::information(this, "Wrong Info",
                             "username or password didn't match");
  }
}

void login::on_lineEdit_password_textChanged(const QString &arg1) {
  password = arg1;
}

void login::on_lineEdit_username_textChanged(const QString &arg1) {
  username = arg1;
}
