#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <string>
#include "Graph.h"

Graph::Graph(){
}

string Graph::data(int k){
  return myAdjacencyLists[k].data;
}

void Graph::read(ifstream & inStream){
  string originCity, destCity, depTime, arrTime, cost;
  VertexInfo vi;
 // Flight f1;
  int n, vertex;
  myAdjacencyLists.push_back(vi);
  for(;;){
    //inStream >> vi.data;
    inStream >> originCity;
    inStream >> destCity;
    inStream >> depTime;
    inStream >> arrTime;
    inStream >> cost;
    Flight f1 = Flight(originCity, destCity, depTime, arrTime, cost);
    // f1.show();
    City c1 = City(originCity);
    c1.addFlight(f1);
    cities.push_back(c1);
//Watch out for repeats we need to fix this
     
   if(inStream.eof()) break;
    //inStream >> n;
    n = 4;
    //cout << "N is " << n << endl;
    list<int> adjList;
    for(int i = 1; i <= n; i++){
      //inStream >> vertex;
      //adjList.push_back(vertex);
    }
    vi.adjacencyList = adjList;
    myAdjacencyLists.push_back(vi);
  }
}

void Graph::show(){
  for(int i = 0; i < cities.size(); i++){
    for(int j = 0; j < cities[i].getFlights().size(); j++){
      cities[i].getFlights()[j].show();
    }
  }
}
