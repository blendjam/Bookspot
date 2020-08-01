#ifndef LOGIN_H
#define LOGIN_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase userInfo;

public:
    void dbClose();
    bool dbOpen();

public:
    Login(QWidget *parent = nullptr);
    void setTableName(QString name, int index);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
    QString tableID;
};
#endif // LOGIN_H
