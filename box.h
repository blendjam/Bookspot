#ifndef BOX_H
#define BOX_H

#include <QRadioButton>
#include <QMessageBox>
#include <QString>

class Box : public QRadioButton
{
    Q_OBJECT
    QString type;
public:
    Box(QString type,QWidget *parent = nullptr);
    void onClick();
    void showVehicle(QString type);
};

#endif // BOX_H
