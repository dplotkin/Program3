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
    inStream >> vi.data;
    cout << "VI data is " << vi.data << endl;
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
