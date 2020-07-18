#ifndef BOX_H
#define BOX_H

#include <QRadioButton>
#include <QMessageBox>

class Box : public QRadioButton
{

    Q_OBJECT

private:
    bool isActive;

public:
    Box(QWidget *parent = nullptr);
    void setActive(bool value);

public slots:
    // void onClick();
};

#endif // BOX_H
