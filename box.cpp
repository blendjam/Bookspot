#include "box.h"

Box::Box(QWidget *parent) : QRadioButton(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    this->setStyleSheet("Box::disabled{image: url(:/resourses/img/parked.png)}");
}
