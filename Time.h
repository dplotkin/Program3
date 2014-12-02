/*
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
*/
#ifndef _Time_H_
#define _Time_H_
class Time;
using namespace std;

class Time
{
	private:
		time_t timestamp;

  	public:
  		Time();
  		Time(const int&, const int&);// Get 9:45pm with arguments 21 and 45.
  		Time(const int&, const int&, const string&);// Get 9:45pm with arguments 9, 45 and pm.
  		Time(const string &);// Get 8:38am with argument "8:38am"

  		void getTime(const int&, const int&);// myTime.getTime(17, 45); <-- Uses military time.
  		void getTime(const int&, const int&, const string&);// myTime.getTime(5, 45, "pm");
  		void getTime(const string&);// myTime.getTime("5:45pm"); <-- Time supplied as string.
  		void getTime(const time_t&);// time_t timestamp = 1377662400; myTime.getTime(timestamp);

  		time_t returnTimestamp();// cout << myTime.returnTimestamp() ... prints 1419483600
  		string returnTimeAsString(); // cout << myTime.returnTimeAsString() ... prints 5:45pm

  		friend int operator-(const Time&, const Time&);// (myTime2 - myTime1) yields time difference in seconds.
  		friend bool operator>(const Time&, const Time&);// (myTime2 > myTime1) yields 1 if myTime2 is after myTime1.
  		friend bool operator<(const Time&, const Time&);// (myTime2 < myTime1) yields 1 if myTime2 is before myTime1.
  		friend bool operator>=(const Time&, const Time&);// (myTime2 >= myTime1) yields 1 if myTime2 is larger or equal to myTime1.
  		friend bool operator<=(const Time&, const Time&);// (myTime2 <= myTime1) yields 1 if myTime2 is less than or equal to myTime1.
  		friend bool operator==(const Time&, const Time&);// (myTime2 == myTime1) yields 1 if myTime2 is the same moment as myTime1.
  		friend istream & operator>>(istream &, Time &);// cin >> myTime;
  		friend ostream & operator<<(ostream &, Time &);// cout << myTime;

  		void show();// myTime.show() prints out info useful for debugging Time object
};


#endif
