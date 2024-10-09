#include "Athlete.h"

Athlete :: Athlete()
{
}

Athlete::~Athlete()
{

}

Athlete::Athlete(const Athlete & a)
{
    num      =  a.num;
    name     =  a.name;
    age      =  a.age;
    sex      =  a.sex;
    gender   =  a.gender;
    country  =  a.country;

    mtime    =  a.mtime;
    rank     =  a.rank;
    note     =  a.note;
}

Athlete& Athlete::operator= (const Athlete& a)
{
    this->  num      =  a.num;
    this->  name     =  a.name;
    this->  age      =  a.age;
    this->  sex      =  a.sex;
    this->  gender   =  a.gender;
    this->  country  =  a.country;

    this->  mtime    =  a.mtime;
    this->  rank     =  a.rank;
    this->  note     =  a.note;
    return *this;
}


