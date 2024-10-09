#ifndef ATHLETE_H
#define ATHLETE_H

#include <QObject>
#include "Match_time.h"


class Athlete
{
public:
    Athlete();
    Athlete(const Athlete & athlete);
    Athlete& operator = (const Athlete & athlete);
    virtual ~Athlete();

    void SaveAthlete(QTextStream &aStream);
    void ReadAthlete(QTextStream &aStream);

    int           num=0;         //号码
    QString       name;          //姓名
    int           age;           //年龄
    bool          sex;           //性别
    QString       gender;        //性别
    QString       country;       //国家

    Match_time    mtime;         //用时
    int           rank=100;
    QString       note=" ";
};

#endif // ATHLETE_H
