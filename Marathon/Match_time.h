#ifndef MATCH_Match_time_H
#define MATCH_Match_time_H
#include<iostream>
using namespace std;
#include <QString>


class Match_time
{

public:
    Match_time();
    Match_time(int h,int m,int s);
    Match_time operator+(Match_time &t);
    Match_time operator-(Match_time &t);
    Match_time operator>(Match_time &t);
    int value() const;
    QString displaytime() const;
    void fromSeconds(int totalSeconds);
private:
    int hour;
    int minute;
    int second;

};

#endif // MATCH_Match_time_H
