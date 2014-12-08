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

 private:
  vector<City> cities;
  class VertexInfo{
  public:
    string data;
    list<int> adjacencyList;
};
  vector<VertexInfo> myAdjacencyLists;
};
#endif
