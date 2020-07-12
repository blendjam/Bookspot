#include "box.h"

Box::Box() { }

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
    if (active) {
        this->setIcon(QIcon(":/resourses/img/student.png"));
        this->setIconSize(QSize(this->width() - 10, this->height() - 10));
    }

    else
        this->setIcon(QIcon());
}
