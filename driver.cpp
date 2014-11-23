#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include <string>
#include "Graph.h"

int main(int argc, char * argv[]){
ifstream inFile(argv[1]);
Graph graph;
graph.read(inFile);
inFile.close();
}
