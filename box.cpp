#include "box.h"

Box::Box(const QString &text, QWidget *parent)
    : QRadioButton(text, parent)
{
    connect(this, &QRadioButton::clicked, this, &Box::onClick);
    this->setCursor(Qt::PointingHandCursor);
}

void Box::toggleActive()
{
    active = !active;
}

bool Box::isActive()
{
    return active;
}

void Box::onClick()
{
    toggleActive();
}
