#ifndef BOX_H
#define BOX_H

#include <QRadioButton>
#include <QMessageBox>

class Box : public QRadioButton
{
    Q_OBJECT

public:
    Box(QWidget *parent = nullptr);
};

#endif // BOX_H
