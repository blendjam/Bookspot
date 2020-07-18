#ifndef USER_H
#define USER_H

#include <ctime>
#include <QString>

class User
{

public:
    User(QString username = "", int spot = -1, int startTime = -1, bool booked = false);

public:
    std::time_t bookStartTime;
    QString username;
    int spot;
    bool isBooked;
};

#endif // USER_H
