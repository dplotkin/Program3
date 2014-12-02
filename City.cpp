#include "City.h"
using namespace std;

City::City(){
  //things
}


City::City(string city){
  name = city;
}

void City::addFlight(Flight f){
  flights.push_back(f);
}
string City::getName(){
  return name;
}

vector<Flight> City::getFlights(){
  return flights;
}


