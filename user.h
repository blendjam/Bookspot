#ifndef USER_H
#define USER_H

#include <ctime>
#include <QString>
#include <QDebug>

class User
{

public:
    User() {}
    User(QString name, int spot, int start, bool booked);

public:
    QString username;
    int spot;
    std::time_t bookStartTime;
    bool isBooked;
};

#endif // USER_H
