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
}
