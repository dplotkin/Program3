#include <iostream>
#include "Flight.h"
//#include "Time.h"

using namespace std;
#include <string>

Flight::Flight()
{

}

Flight::Flight(const string &cityFromString, const string &cityToString, const string &timeFromString, const string &timeToString, const string &costString)
{
	(*this).getFlight(cityFromString, cityToString, timeFromString, timeToString, costString);
}

void Flight::getFlight(const string &cityFromAsString, const string &cityToAsString, const string &timeFromAsString, const string &timeToAsString, const string &costAsString)
{
	cityFrom = cityFromAsString;
	cityTo = cityToAsString;
	timeFrom.getTime(timeFromAsString);
	timeTo.getTime(timeToAsString);

	string costAsStringTemp = costAsString;// ... because .erase() doesn't like to work on constant strings.
	cost = stof(costAsStringTemp.erase(0, 1));
}

string Flight::returnCityFrom()
{
	return cityFrom;
}

string Flight::returnCityTo()
{
	return cityTo;
}

string Flight::returnTimeFrom()
{
	return timeFrom.returnTimeAsString();
}

string Flight::returnTimeTo()
{
	return timeTo.returnTimeAsString();
}

time_t Flight::returnTimestampFrom()
{
	return timeFrom.returnTimestamp();
}

time_t Flight::returnTimestampTo()
{
	return timeTo.returnTimestamp();
}

Time Flight::returnTimeFromAsObject()
{
	return timeFrom;
}

Time Flight::returnTimeToAsObject()
{
	return timeTo;
}

float Flight::returnCost()
{
	return cost;
}
 
// a flight's duration is its flight time measured in seconds:
int Flight::returnDuration()
{
	int duration = (int)( timeTo.returnTimestamp() - timeFrom.returnTimestamp() );
	return duration;
}

// When debugging, print out values held in Flight object using myFlight.show():
void Flight::show()
{
	cout << "cityFrom = " << cityFrom << endl;
	cout << "cityTo = " << cityTo << endl;
	cout << "timeFrom = " << timeFrom << endl;
	cout << "timeTo = " << timeTo << endl;
	cout << "cost = $" << cost << endl;
}
