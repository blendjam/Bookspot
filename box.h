#ifndef BOX_H
#define BOX_H

#include <QRadioButton>

class Box : public QRadioButton
{

    Q_OBJECT

private:
    bool active = false;

public:
    Box(QWidget *parent = nullptr);
public slots:
    void onClick();
};

#endif // BOX_H
