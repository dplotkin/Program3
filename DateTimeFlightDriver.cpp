#include <ctime>
#include <iostream>

#include "Date.h"
#include "Flight.h"

using namespace std;

int main () 
{
	cout << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%% playing with the Date class %%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;

	Date myDate;

	cout << endl << "Enter a date (in MM/DD/YYYY format): ";
	cin >> myDate;
	cout << endl << "Entering a date via cin gives the Date object myDate the value " << myDate << "." << endl << endl;

	myDate.getDate(12, 25, 2014);
	cout << "Using myDate.getDate(12, 25, 2014) gives the Date object myDate the value " << myDate << "." << endl << endl;

	myDate.getDate(1419483600);
	cout << "Using myDate.getDate(1419483600) gives the Date object myDate the value  " << myDate << "." << endl << endl;

	Date myDateTwo(10, 31, 2014);
	cout << "Constructing a Date object using the value constructor call myDateTwo(10, 31, 2014) yields " << myDateTwo << "." << endl;

	cout << endl << "myDateTwo > myDate = " << (myDateTwo > myDate) << endl;
	cout << endl << "myDateTwo < myDate = " << (myDateTwo < myDate) << endl;
	cout << endl << "myDateTwo >= myDate = " << (myDateTwo >= myDate) << endl;
	cout << endl << "myDateTwo <= myDate = " << (myDateTwo <= myDate) << endl;
	cout << endl << "myDateTwo == myDate = " << (myDateTwo == myDate) << endl;

	cout << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%% playing with the Time class %%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;

	Time myTimeA(19, 42);
	cout << endl << "myTimeA = " << myTimeA << endl;

	Time myTimeB(7, 36, "am");
	cout << "myTimeB = " << myTimeB << endl;

	Time myTimeC("8:38am");
	cout << "myTimeC = " << myTimeC<< endl;


	Time myTime;
	myTime.getTime(17, 45);
	cout << endl << "Using myTime.getTime(17, 45) gives the Time object myTime the value " << myTime << "." << endl;

	Time myTimeTwo;
	myTimeTwo.getTime("10:07pm");
	cout << endl << "Using myTimeTwo.getTime(\"10:07pm\") gives the Time object myTimeTwo the value " << myTimeTwo << "." << endl << endl;

	cout << "Enter a time of day (like 5:45pm): ";
	Time myTimeThree;
	cin >> myTimeThree;
	cout << endl << "Using cin >> myTimeThree, the Time object myTimeThree gets the value " << myTimeThree << "." << endl;

	Time myTimeFour;
	myTimeFour.getTime(5, 45, "am");
	cout << endl << "Using myTimeFour.getTime(5, 45, \"am\") gives the Time object myTimeFour the value " << myTimeFour << "." << endl;
	cout << "myTimeFour.returnTimeAsString(): " << myTimeFour.returnTimeAsString() << endl;

	Time myTimeFive;
	myTimeFive.getTime(-2208950100); 
	cout << endl << "Using myTimeFive.getTime(-2208950100) gives the Time object myTimeFive the value " << myTimeFive << "." << endl;

	cout << endl << "myTimeTwo - myTime = " << myTimeTwo - myTime << endl;
	cout << endl << "myTimeTwo > myTime = " << (myTimeTwo > myTime) << endl;
	cout << endl << "myTimeTwo < myTime = " << (myTimeTwo < myTime) << endl;
	cout << endl << "myTimeTwo >= myTime = " << (myTimeTwo >= myTime) << endl;
	cout << endl << "myTimeTwo <= myTime = " << (myTimeTwo <= myTime) << endl;
	cout << endl << "myTimeTwo == myTime = " << (myTimeTwo == myTime) << endl;


	cout << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%% playing with the Flight class %%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;

	Flight myFlight;
	myFlight.getFlight("Boston", "Baltimore", "5:40am", "9:19am", "$219");
	cout << endl << "myFlight:" << endl;
	myFlight.show();

	Flight myFlightTwo("Binghamton", "Santiago", "1:25pm", "5:40pm", "$589");
	cout << endl << "myFlightTwo:" << endl;
	cout << "duration: " << myFlightTwo.returnDuration() << endl;
	cout << "cityFrom: " << myFlightTwo.returnCityFrom() << endl;
	cout << "cityTo: " << myFlightTwo.returnCityTo() << endl;

	Time timeFromTwo = myFlightTwo.returnTimeFromAsObject();
	Time timeToTwo = myFlightTwo.returnTimeToAsObject();
	cout << "timeFrom: " << timeFromTwo << endl;
	cout << "timeTo: " << timeToTwo << endl;
	cout <<  "timeToTwo - timeFromTwo = " << timeToTwo - timeFromTwo << endl;
	cout << "timestampFrom: " << myFlightTwo.returnTimestampFrom() << endl;
	cout << "timestampTo: " << myFlightTwo.returnTimestampTo() << endl;
	cout << "cost: " << myFlightTwo.returnCost() << endl << endl;

	return 0;
}// end fn main.
