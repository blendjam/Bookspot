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

 private:
  Ui::login *ui;
  MainWindow main_window;
};
#endif  // LOGIN_H
