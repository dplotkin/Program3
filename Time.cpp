/*
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include "Time.h"

Time::Time(){
}

Time::Time(string inputTime){
}

Time Time::operator+(const Time &right){
}

Time Time::operator-(const Time &right){
}

bool Time::operator==(const Time &right){
}
*/

#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Time.h"

#define EST 5

using namespace std;

Time::Time()
{

}

// value constructor with military hour and minute as arguments:
Time::Time(const int &milHr, const int &min)
{
	(*this).getTime(milHr, min);
}

// value constructor with hour, minute and am/pm as arguments:
Time::Time(const int &hr, const int &min, const string &am_pm)
{
	(*this).getTime(hr, min, am_pm);
}

// value constructor with argument "8:38":
Time::Time(const string &paramTimeAsString)
{
	(*this).getTime(paramTimeAsString);
}

// Assign (military) hour and minute values to Time object using myTime.getTime(17, 45):
void Time::getTime(const int &hrMilitary, const int &min)
{
	struct tm timeStruct;

	timeStruct.tm_year = 0;// 0 --> year 1900
	timeStruct.tm_mon = 0;// 0 --> January
	timeStruct.tm_mday = 1;// 1 --> 1st day of month

	timeStruct.tm_hour = hrMilitary + EST;   
	timeStruct.tm_min = min;
	timeStruct.tm_sec = 0;

	timestamp = timegm(&timeStruct);
}

// Assign hour, minute and am/pm values to Time object using myTime.getTime(5, 45, "pm"):
void Time::getTime(const int &hours, const int &minutes, const string &am_pm)
{
	struct tm timeStruct;

	timeStruct.tm_year = 0;// 0 --> year 1900
	timeStruct.tm_mon = 0;// 0 --> January
	timeStruct.tm_mday = 1;// 1 --> 1st day of month

	int hoursMilitary;
	
	if (am_pm == "pm")
	{// ... it's pm.
		if (hours == 12)
			hoursMilitary = 12;
		else
			hoursMilitary = hours + 12;
	}
	else
	{// ... it's am.
		if (hours == 12)
			hoursMilitary = 0;
		else
			hoursMilitary = hours;
	}

	timeStruct.tm_hour = hoursMilitary + EST;   
	timeStruct.tm_min = minutes;
	timeStruct.tm_sec = 0;

	timestamp = timegm(&timeStruct);
}

// Assign hour, minute and am/pm values (provided as string) to Time object using myTime.getTime("5:45pm"):
void Time::getTime(const string &timeAsString)
{
	int sizeString = timeAsString.size();
	int hours;
	int hoursMilitary;
	int minutes;
	string am_pm;

	minutes = atoi( ( timeAsString.substr((sizeString - 4), 2) ).c_str() );

	am_pm = timeAsString.substr((sizeString - 2), 2);
	
	if (timeAsString.size() > 6)// 11:15am, for instance, contains 7 characters.
		hours = atoi( ( timeAsString.substr(0, 2) ).c_str() );
	else// 1:15am, for instance.
		hours = atoi( ( timeAsString.substr(0, 1) ).c_str() );

	if (am_pm == "pm")
	{// ... it's pm.
		if (hours == 12)
			hoursMilitary = 12;
		else
			hoursMilitary = hours + 12;
	}
	else
	{// ... it's am.
		if (hours == 12)
			hoursMilitary = 0;
		else
			hoursMilitary = hours;
	}

	(*this).getTime(hoursMilitary, minutes);
}

// Assign hour and minute values toTime object using timestamp ... myTime.getTime(1377662400):
void Time::getTime(const time_t &tstamp)
{
	timestamp = tstamp;
}

// myTime.returnTimestamp yields the timestamp for Time object myTime:
time_t Time::returnTimestamp()
{
	return(timestamp);
}

// myTime.returnTimeAsString yields theme ti as a string in HH:MMpm format:
string Time::returnTimeAsString()
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime(&timestamp);
	int hour = ptrTimeStruct->tm_hour;
	int minute = ptrTimeStruct->tm_min;
	
	string hourString;
	string minuteString;
	string amPmString;


	if (hour >= 12)
		amPmString = "pm";
	else
		amPmString = "am";

	if (hour == 0 || hour == 12)
		hour = 12;
	else
		hour = hour % 12;
	hourString = to_string(hour);

	if (minute < 10)
		minuteString = ":0" + to_string(minute);
	else
		minuteString = ":" + to_string(minute);

	return(hourString + minuteString + amPmString);
}


// Assign hour and minute values to Time object using cin >> myTime:
istream &operator>>(istream &in, Time &paramTime)
{
	char colon;
	int hours;
	int hoursMilitary;
	int minutes;
	char a_p;

	in >> hours >> colon >> minutes >> a_p;

	if (a_p == 'p')
	{// ... it's pm.
		if (hours == 12)
			hoursMilitary = 12;
		else
			hoursMilitary = hours + 12;
	}
	else
	{// ... it's am.
		if (hours == 12)
			hoursMilitary = 0;
		else
			hoursMilitary = hours;
	}

	paramTime.getTime(hoursMilitary, minutes);

	return (in);  
}

// Print out Time object in HH:MMam format using cout << myTime:
ostream &operator<<(ostream &out, Time &paramTime)
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime( &(paramTime.timestamp) );
	int hour = ptrTimeStruct->tm_hour;
	int minute = ptrTimeStruct->tm_min;
	string am_pm;
	if (hour >= 12)
		am_pm = "pm";
	else
		am_pm = "am";

	if (hour == 0 || hour == 12)
		hour = 12;
	else
		hour = hour % 12;

	if (minute < 10)
		out << hour << ":0" << minute << am_pm;
	else
		out << hour << ':' << minute << am_pm;
   	
   	return out;
}

// (myTime2 - myTime1) yields time difference in seconds:
int operator-(const Time& leftTime, const Time& rightTime) 
{
	time_t timeDifferenceInSeconds = leftTime.timestamp - rightTime.timestamp;

   	return (int)timeDifferenceInSeconds;
}

// (myTime2 > myTime1) yields 1 if myTime2 is larger:
bool operator>(const Time& leftTime, const Time& rightTime) 
{
	bool leftTimeIsGreaterThanRightTime = false;
	if (leftTime.timestamp > rightTime.timestamp)
		leftTimeIsGreaterThanRightTime = true;
   	return leftTimeIsGreaterThanRightTime;
}

// (myTime2 < myTime1) yields 1 if myTime2 is smaller:
bool operator<(const Time& leftTime, const Time& rightTime) 
{
	bool leftTimeIsLessThanRightTime = false;
	if (leftTime.timestamp < rightTime.timestamp)
		leftTimeIsLessThanRightTime = true;
   	return leftTimeIsLessThanRightTime;
}

// (myTime2 >= myTime1) yields 1 if myTime2 is larger or equal to myTime1:
bool operator>=(const Time& leftTime, const Time& rightTime) 
{
	bool leftTimeIsGreaterOrEqualToRightTime = false;
	if (leftTime.timestamp >= rightTime.timestamp)
		leftTimeIsGreaterOrEqualToRightTime = true;
   	return leftTimeIsGreaterOrEqualToRightTime;
}

// (myTime2 <= myTime1) yields 1 if myTime2 is less than or equal to myTime1:
bool operator<=(const Time& leftTime, const Time& rightTime) 
{
	bool leftTimeIsLessThanOrEqualToRightTime = false;
	if (leftTime.timestamp <= rightTime.timestamp)
		leftTimeIsLessThanOrEqualToRightTime = true;
   	return leftTimeIsLessThanOrEqualToRightTime;
}

// (myTime2 == myTime1) yields 1 if myTime2 is equal to myTime1:
bool operator==(const Time& leftTime, const Time& rightTime) 
{
	bool leftTimeIsEqualToRightTime = false;
	if (leftTime.timestamp == rightTime.timestamp)
		leftTimeIsEqualToRightTime = true;
   	return leftTimeIsEqualToRightTime;
}

// When debugging, print out values held in Date object using myTime.show():
void Time::show()
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime(&timestamp);
	cout << "timestamp = " << timestamp << endl;
	cout << "ptrTimeStruct->tm_year = " << ptrTimeStruct->tm_year << "; human year = "<< (ptrTimeStruct->tm_year + 1900) << endl;
	cout << "ptrTimeStruct->tm_mon = " << ptrTimeStruct->tm_mon << "; human month = "<< (ptrTimeStruct->tm_mon + 1) << endl;
	cout << "ptrTimeStruct->tm_mday = " << ptrTimeStruct->tm_mday << "; human day = "<< (ptrTimeStruct->tm_mday) << endl;

	cout << "ptrTimeStruct->tm_hour = " << ptrTimeStruct->tm_hour << endl;
	cout << "ptrTimeStruct->tm_min = " << ptrTimeStruct->tm_min << endl;
	cout << "ptrTimeStruct->tm_sec = " << ptrTimeStruct->tm_sec << endl;
	cout << endl;
} 