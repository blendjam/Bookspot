#include "user.h"

User::User(QString username, int spot, int startTime, bool booked) : username(username), spot(spot), bookStartTime(startTime), isBooked(booked)
{
}
