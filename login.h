#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QMainWindow {
  Q_OBJECT

 public:
  login(QWidget *parent = nullptr);
  ~login();

 private slots:
  void on_pushButton_clicked();

  void on_lineEdit_password_textChanged(const QString &arg1);
  void on_lineEdit_username_textChanged(const QString &arg1);

 private:
  Ui::login *ui;
  MainWindow main_window;
  QString password;
  QString username;
};
#endif  // LOGIN_H
