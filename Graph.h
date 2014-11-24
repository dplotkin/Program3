#include <vector>
#include <list>
#include <iostream>
#include <fstream>

#ifndef _Graph_H_
#define _Graph_H_

class Graph;

class Graph{
 public:
  Graph();
  string data(int);
  void read(ifstream &);
  
 private:
  class VertexInfo{
  public:
    string data;
    list<int> adjacencyList;
};
  vector<VertexInfo> myAdjacencyLists;
};
#endif

