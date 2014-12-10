#ifndef _Graph_H_
#define _Graph_H_

class Graph;

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "Flight.h"
#include "City.h"
class Graph{
 public:
  Graph();
  string data(int);
  void read(ifstream &);
  void show();

  void showFlightsFromCity(const string &);
  Flight returnFlightWithEarliestPossibleArrival(const string &, const string &, const Time &);
  Flight returnFlightForFewestHops(const string &, const string &);
  vector<Flight> runDijkstraAlgorithm(const string &, const string &, const char &);
  void oneDijkstraPass(int, int*, int*, vector<Flight> &, const vector<string> &, const char &);
  
  vector<Flight> getCheapestItinerary(const string &, const string &, const Time &);
  void depthFirstSearch(const string &, const string &, const Time &);
  bool hasBeenVisited(string);

 private:
  vector<City> cities;
  vector<string> visitedCities;
  vector<Flight> itinerary;
  vector<vector<Flight>> itineraries;
  int numItineraries;
  class VertexInfo{
  public:
    string data;
    list<int> adjacencyList;
};
  vector<VertexInfo> myAdjacencyLists;
};
#endif
