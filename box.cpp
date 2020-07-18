#include "box.h"

Box::Box(QWidget *parent)
    : QRadioButton(parent),
      isActive(false)
{
    // connect(this, &QRadioButton::clicked, this, &Box::onClick);
    this->setCursor(Qt::PointingHandCursor);
}

void Box::setActive(bool value)
{
    isActive = value;
    if (isActive)
    {
        this->setStyleSheet("image: url(:/resourses/img/student.png)");
    }
}

// void Box::onClick()
// {
// isActive = this->isChecked();
// }
