#ifndef BOX_H
#define BOX_H

#include <QRadioButton>

class Box : public QRadioButton
{

    Q_OBJECT

private:
    bool active = false;

public:
    Box() {}
    Box(const QString &text, QWidget *parent = nullptr);
    void toggleActive();
    bool isActive();
public slots:
    void onClick();
};

#endif // BOX_H
