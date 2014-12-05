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
    //f1.show();

    City c1 = City(originCity);
    c1.addFlight(f1);

    // %%%%% start george's addition %%%%%

    City c2 = City(destCity);

    bool c1AlreadyInCities = false;
    bool c2AlreadyInCities = false;
    for (vector<City>::iterator it = cities.begin() ; it != cities.end(); ++it)
    {
      if ( (*it).getName() == c1.getName())
      {
        c1AlreadyInCities = true;
        (*it).addFlight(f1);
      }

      if ( (*it).getName() == c2.getName())
        c2AlreadyInCities = true; 
    }

    if (!c1AlreadyInCities)
    {
      c1.addFlight(f1);
      cities.push_back(c1);
    }
   
    if (!c2AlreadyInCities)
    {
      cities.push_back(c2);    
    }

    // %%%%% end george's addition %%%%%

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

void Graph::showFlightsFromCity(const string &nameCity)
{
  for(int i = 0; i < cities.size(); i++)
  {
    if (cities[i].getName() == nameCity)
    {
      for(int j = 0; j < cities[i].getFlights().size(); j++)
      {
        cities[i].getFlights()[j].show();
      }
    }
  }
}

Flight Graph::returnFlightWithEarliestPossibleArrival(const string &cityFrom, const string &cityTo, const Time & earliestPossibleTimeFrom)
{
  Flight flightWithEarliestPossibleArrival("phonyCityFrom", "phonyCityTo", "11:59pm", "11:59pm", "$999");

  for(int i = 0; i < cities.size(); i++)//.size() = total number of flights
  {
    if (cities[i].getName() == cityFrom)
    {
      for(int j = 0; j < cities[i].getFlights().size(); j++)// j = index of flight in flights vector.
      {// Loop through flights leaving the city cities[i].
        if (cities[i].getFlights()[j].returnCityTo() == cityTo && cities[i].getFlights()[j].returnTimeFrom() >= earliestPossibleTimeFrom)
        {// ... the flight goes to the city specified, and it leaves after the predecessor flight arrives. 
          if (cities[i].getFlights()[j].returnTimeTo() <= flightWithEarliestPossibleArrival.returnTimeTo())
            // ... then the flight's the earliest flight *arriving* at the city specified.
            flightWithEarliestPossibleArrival = cities[i].getFlights()[j];
        }
      }// end for j loop.
    }// end if.
  }// end for i loop.

  return flightWithEarliestPossibleArrival; 
}

void Graph::runDijkstraAlgorithm(const string &citySource, const string &cityDest)
{
  vector<string> cityNamesByIndex;
 
  // Need to put citySource into cityNamesByIndex[0] and cityDest into cityNamesByIndex[last]
  for(int i = 0; i < cities.size(); i++)
  {
    cityNamesByIndex.push_back( cities[i].getName() );
  }
  
  /*
  for (int i = 0; i < cityNamesByIndex.size(); i++)
  {
    cout << "cityNamesByIndex[i] = " << cityNamesByIndex[i] << endl;
  }
  */
}



