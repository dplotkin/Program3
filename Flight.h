#include "Time.h"

using namespace std;

class Flight
{
	private:
		string cityFrom;
		string cityTo;
		Time timeFrom;
		Time timeTo;
		float cost;

  	public:
  		Flight();
  		Flight(const string &, const string &, const string &, const string &, const string &);
  		void getFlight(const string &, const string &, const string &, const string &, const string &);
  		string returnCityFrom();
  		string returnCityTo();
  		string returnTimeFrom();
  		string returnTimeTo();
  		time_t returnTimestampFrom();
  		time_t returnTimestampTo();
  		Time returnTimeFromAsObject();
  		Time returnTimeToAsObject();
  		float returnCost();

  		int returnDuration();
  		void show();

};