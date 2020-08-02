#include "user.h"

User::User(QString name, int spot, int startTime, bool booked)
{
    this->username = name;
    this->spot = spot;
    this->bookStartTime = startTime;
    this->isBooked = booked;
}
