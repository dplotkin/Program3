#ifndef _Date_H_
#define _Date_H_
class Date;

using namespace std;

class Date
{
	private:
		time_t timestamp;

  	public:
  		Date();
  		Date(const int&, const int&, const int&);// Date(12, 25, 2014);

  		void getDate(const int&, const int&, const int&);// myDate.getDate(12, 25, 2014);
  		void getDate(const time_t&);// int timestamp = 1377662400; myDate.getDate(timestamp);

  		int returnMonth();// cout << myDate.returnMonth() ... prints 12
  		int returnDay();// cout << myDate.returnDay() ... prints 25
  		int returnYear();// cout << myDate.returnYear() ... prints 2014
  		time_t returnTimestamp();// cout << myDate.returnTimestamp() ... prints 1419483600
  		string returnDateAsString(); // cout << myDate.returnDateAsString() ... prints 12/25/2014

  		friend bool operator>(const Date&, const Date&);// (myDate2 > myDate1) yields 1 if myDate2 is after myDate1.
  		friend bool operator<(const Date&, const Date&);// (myDate2 < myDate1) yields 1 if myDate2 is before myDate1.
  		friend bool operator>=(const Date&, const Date&);// (myDate2 >= myDate1) yields 1 if myDate2 is larger or equal to myDate1.
  		friend bool operator<=(const Date&, const Date&);// (myDate2 <= myDate1) yields 1 if myDate2 is less than or equal to myDate1.
  		friend bool operator==(const Date&, const Date&);// (myDate2 == myDate1) yields 1 if myDate2 is the same day as myDate1.
  		friend istream & operator>>(istream &, Date &);// cin >> myDate;
  		friend ostream & operator<<(ostream &, Date &);// cout << myDate;

  		void show();// myDate.show() prints out info useful for debugging Date object
};

#endif
