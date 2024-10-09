#include "Match_time.h"

Match_time::Match_time()
{
    hour=24;
    minute=0;
    second=0;
}
Match_time::Match_time(int h,int m,int s)
{
    hour=h;
    minute=m;
    second=s;

    if(hour<0)
    {
        cout<<"输入时间错误"<<endl;
    }
    if(minute>=60)
        hour+=1;
    minute%=60;
    if(minute<0)
    {
        hour-=1;
        minute+=60;
    }
    if(second<0)
    {
        minute-=1;
        second+=60;
    }
    if(second>=60)
        minute+=1;
    second%=60;
}
Match_time Match_time::operator+(Match_time &t)
{
    return Match_time(hour+t.hour,minute+t.minute,second+t.second);
}
Match_time Match_time::operator-(Match_time &t)
{
    return Match_time(hour-t.hour,minute-t.minute,second-t.second);
}

int Match_time::value() const
{
    int value=0;
    value=(this->second+this->minute*60+this->hour*3600);
    return value;
}

QString Match_time::displaytime() const
{
    if(hour!=24)
    {
    return QString("%1:%2:%3")
        .arg(hour, 2, 10, QChar('0'))   // 保证小时至少有两位，前面补 0
        .arg(minute, 2, 10, QChar('0')) // 保证分钟至少有两位，前面补 0
        .arg(second, 2, 10, QChar('0')); // 保证秒数至少有两位，前面补 0
    }
    else
    {
        return "NULL";
    }
}

void Match_time::fromSeconds(int totalSeconds)
{
    // 计算小时、分钟、秒
    hour = totalSeconds / 3600;      // 1小时 = 3600秒
    totalSeconds %= 3600;            // 剩余的秒数
    minute = totalSeconds / 60;      // 1分钟 = 60秒
    second = totalSeconds % 60;      // 剩余的秒数就是秒

    // 检查是否有负值情况
    if (hour < 0 || minute < 0 || second < 0)
    {
        cout << "输入时间错误" << endl;
        hour = 0;
        minute = 0;
        second = 0;
    }
}
