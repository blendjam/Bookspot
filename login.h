#ifndef LOGIN_H
#define LOGIN_H

#include <QDebug>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QtSql>

#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class login;
}
QT_END_NAMESPACE

class login : public QMainWindow {
    Q_OBJECT
public:
    QSqlDatabase userInfo;

public:
    void dbClose();
    bool dbOpen();

public:
    login(QWidget* parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login* ui;

};
#endif // LOGIN_H
