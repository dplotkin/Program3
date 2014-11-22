#include <iostream>
using namespace std;
#include <string>

#ifndef _Time_H_
#define _Time_H_

class Time;

class Time{
public:
Time();
Time(string);
bool &operator==(const Time &);
Time &operator+(const Time &);
Time &operator-(const Time &);

private:

};
#endif
