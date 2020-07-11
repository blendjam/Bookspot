#include "box.h"

Box::Box(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{
    connect(this, &QPushButton::clicked, this, &Box::onClick);
}

void Box::toggleActive()
{
    active = !active;
}

void Box::onClick()
{
    toggleActive();
    if (active)
        this->setIcon(QIcon(":/resourses/img/student.png"));
    else
        this->setIcon(QIcon());
}
