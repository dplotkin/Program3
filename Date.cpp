#include <ctime>
#include <iostream>
#include <string>
#include "Date.h"

#define EST 5

using namespace std;

Date::Date()
{

}

Date::Date(const int &mo, const int &dy, const int &yr)
{
	(*this).getDate(mo, dy, yr);
}

// Assign month, date and year values to Date object using myDate.getDate(7, 4, 2014):
void Date::getDate(const int &mo, const int &dy, const int &yr)
{
	struct tm timeStruct;

	timeStruct.tm_year = yr - 1900; 
	timeStruct.tm_mon = mo - 1; // January = 0, February = 1 ...
	timeStruct.tm_mday = dy;

	timeStruct.tm_hour = 0 + EST;   
	timeStruct.tm_min = 0; 
	timeStruct.tm_sec = 0;

	timestamp = timegm(&timeStruct);
}

// Assign month, date and year values to Date object using timestamp ... myDate.getDate(1377662400):
void Date::getDate(const time_t &tstamp)
{
	timestamp = tstamp;
}

// myDate.returnTimestamp yields the timestamp for Date object myDate:
time_t Date::returnTimestamp()
{
	return(timestamp);
}

// myDate.returnMonth yields the month for Date object myDate:
int Date::returnMonth()
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime(&timestamp);

	return( ptrTimeStruct->tm_mon + 1 );
}

// myDate.returnDay yields the day (number) for Date object myDate:
int Date::returnDay()
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime(&timestamp);

	return(ptrTimeStruct->tm_mday);
}

// myDate.returnYear yields the year for Date object myDate:
int Date::returnYear()
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime(&timestamp);

	return(ptrTimeStruct->tm_year + 1900);
}

// myDate.returnDateAsString yields the date as a string in MM/DD/YYYY format:
string Date::returnDateAsString()
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime(&timestamp);
	int month = ptrTimeStruct->tm_mon + 1;
	int day = ptrTimeStruct->tm_mday;
	int year = ptrTimeStruct->tm_year + 1900;
	
	string monthString;
	string dayString;
	string yearString;
	string dateString;

	if (month < 10)
		monthString = "0" + to_string(month);
	else
		monthString = to_string(month);

	if (day < 10)
		dayString = "0" + to_string(day);
	else
		dayString = to_string(day);

	yearString = to_string(year);

	dateString = monthString + "/" + dayString + "/" + yearString;

	return(dateString);
}

// (myDate2 > myDate1) yields 1 if myDate2 is after myDate1:
bool operator>(const Date& leftDate, const Date& rightDate) 
{
	bool leftDateIsGreaterThanRightDate = false;
	if (leftDate.timestamp > rightDate.timestamp)
		leftDateIsGreaterThanRightDate = true;
   	return leftDateIsGreaterThanRightDate;
}

// (myDate2 < myDate1) yields 1 if myDate2 is before myDate1:
bool operator<(const Date& leftDate, const Date& rightDate) 
{
	bool leftDateIsLessThanRightDate = false;
	if (leftDate.timestamp < rightDate.timestamp)
		leftDateIsLessThanRightDate = true;
   	return leftDateIsLessThanRightDate;
}

// (myDate2 >= myDate1) yields 1 if myDate2 is larger or equal to myDate1:
bool operator>=(const Date& leftDate, const Date& rightDate) 
{
	bool leftDateIsGreaterOrEqualToRightDate = false;
	if (leftDate.timestamp >= rightDate.timestamp)
		leftDateIsGreaterOrEqualToRightDate = true;
   	return leftDateIsGreaterOrEqualToRightDate;
}

// (myDate2 <= myDate1) yields 1 if myDate2 is less than or equal to myDate1:
bool operator<=(const Date& leftDate, const Date& rightDate) 
{
	bool leftDateIsLessThanOrEqualToRightDate = false;
	if (leftDate.timestamp <= rightDate.timestamp)
		leftDateIsLessThanOrEqualToRightDate = true;
   	return leftDateIsLessThanOrEqualToRightDate;
}
 
// (myDate2 == myDate1) yields 1 if myDate2 is the same day as myDate1:
bool operator==(const Date& leftDate, const Date& rightDate) 
{
	bool leftDateIsEqualToRightDate = false;
	if (leftDate.timestamp == rightDate.timestamp)
		leftDateIsEqualToRightDate = true;
   	return leftDateIsEqualToRightDate;
}

// Assign month, date and year values to Date object using cin >> myDate:
istream &operator>>(istream &in, Date &paramDate)
{
	char ch;
	int mo;
	int dy;
	int yr;

	in >> mo >> ch >> dy >> ch >> yr;

	struct tm timeStruct;
	timeStruct.tm_year = yr - 1900; 
	timeStruct.tm_mon = mo - 1; // January = 0, February = 1 ...
	timeStruct.tm_mday = dy;

	timeStruct.tm_hour = 0 + EST;   
	timeStruct.tm_min = 0; 
	timeStruct.tm_sec = 0;

	paramDate.timestamp = timegm(&timeStruct);
	return (in);  
}

// Print out Date object in M/D/YYYY format using cout << myDate:
ostream &operator<<(ostream &out, Date &paramDate)
{
	struct tm* ptrTimeStruct;
	ptrTimeStruct = localtime( &(paramDate.timestamp) );
	int humanMonth = ptrTimeStruct->tm_mon + 1;
	int humanDay = ptrTimeStruct->tm_mday;
	int humanYear = ptrTimeStruct->tm_year + 1900;

	out << humanMonth << '/' << humanDay << '/' << humanYear;
   	
   	return out;
}

// When debugging, print out values held in Date object using myDate.show():
void Date::show()
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