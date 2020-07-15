#include "box.h"

Box::Box(QWidget *parent)
    : QRadioButton(parent)
{
    connect(this, &QRadioButton::clicked, this, &Box::onClick);
    this->setCursor(Qt::PointingHandCursor);
}

void Box::onClick()
{
    active = this->isChecked();
}
