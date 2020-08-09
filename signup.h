#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QtSql>
#include <QString>

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    QSqlDatabase userinfo;

public:
    bool dbOpen();
    void dbClose();
public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Signup *ui;
};

#endif // SIGNUP_H
