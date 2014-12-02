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

