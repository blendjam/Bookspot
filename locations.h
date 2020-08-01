#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <QDialog>
#include "login.h"

namespace Ui
{
    class Locations;
}

class Locations : public QDialog
{
    Q_OBJECT

public:
    explicit Locations(QWidget *parent = nullptr);
    ~Locations();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Locations *ui;
    Login loginDialog;
};

#endif // LOCATIONS_H
