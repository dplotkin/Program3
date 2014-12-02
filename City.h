#ifndef City_H_
#define City_H_

class City;

#include "Flight.h"
#include "Time.h"
#include "Date.h"
#include <string>
#include <vector>
using namespace std;

class City{
 public:
  City();
  City(string name);
  void addFlight(Flight f);
  string getName();
  //add how to get flights in the future
 private:
  string name;
  vector<Flight> flights;

};

#endif
  
  
