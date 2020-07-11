#ifndef BOX_H
#define BOX_H

#include <QPushButton>

class Box : public QPushButton {

    Q_OBJECT

private:
    bool active = false;

public:
    Box(const QString& text, QWidget* parent = nullptr);
    void toggleActive();
public slots:
    void onClick();
};

#endif // BOX_H
