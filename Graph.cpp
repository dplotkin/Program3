#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
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
    // george commented out: c1.addFlight(f1);

    // %%%% start george's addition %%%%%

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
  Flight flightWithEarliestPossibleArrival("NULL", "NULL", "12:00am", "11:59pm", "$999998");

  for(int i = 0; i < cities.size(); i++)//.size() = total number of flights
  {
    if (cities[i].getName() == cityFrom)
    {
      for(int j = 0; j < cities[i].getFlights().size(); j++)// j = index of flight in flights vector.
      {// Loop through flights leaving the city cities[i].
        if (cities[i].getFlights()[j].returnCityTo() == cityTo && cities[i].getFlights()[j].returnTimeFrom() >= earliestPossibleTimeFrom)
        {// ... the flight goes to the city specified, and it leaves after the predecessor flight arrives.
          if (cities[i].getFlights()[j].returnTimestampTo() <= flightWithEarliestPossibleArrival.returnTimestampTo())
          {// ... then the flight's the earliest flight *arriving* at the city specified.
            flightWithEarliestPossibleArrival = cities[i].getFlights()[j];
          }
        }
      }// end for j loop.
    }// end if.
  }// end for i loop.

  return flightWithEarliestPossibleArrival; 
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%% fn runDijkstraAlgorithm %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

vector<Flight> Graph::runDijkstraAlgorithm(const string &citySource, const string &cityDest, const char &searchOption)
{
  bool debugModeOn = false;
  vector<string> cityNamesByIndex;
  vector<Flight> shortestPath;

  int numberOfVertices = cities.size();

  // Put all cities into vector cityNamesByIndex:
  for(int i = 0; i < numberOfVertices; i++)
  {
    cityNamesByIndex.push_back( cities[i].getName() );
  }

  // # Put SOURCE city into cityNamesByIndex[0] and DESTINATION city into cityNamesByIndex[cities.size() - 1] #

  for (int i = 0; i < numberOfVertices; i++)
  {
    if (cityNamesByIndex[i] == citySource)
    {
      string tempCityName = cityNamesByIndex[0];
      cityNamesByIndex[0] = cityNamesByIndex[i];
      cityNamesByIndex[i] = tempCityName;
    }

    if (cityNamesByIndex[i] == cityDest)
    {
      string tempCityName = cityNamesByIndex[cityNamesByIndex.size() - 1];
      cityNamesByIndex[cityNamesByIndex.size() - 1] = cityNamesByIndex[i];
      cityNamesByIndex[i] = tempCityName;
    }
  }// end for i loop.

  int negOneIfVertexInSetS[numberOfVertices];
  int distToCity[numberOfVertices];

  // ###################### all vertices start in Set Q ######################

  for (int i = 0; i < numberOfVertices; i++)
  {
    // When vertex is still in Q, negOneIfVertexInSetS[i] is positive:
    negOneIfVertexInSetS[i] = i;
  }

  // Put our source vertex 0 in Set S and make dist[0] zero:
  negOneIfVertexInSetS[0] = -1;
  distToCity[0] = 0;

  vector<Flight> flightToCity;
  Flight nullFlight("NULL", "NULL", "12:00am", "11:59pm", "$999999");

  // ########## Populate vector flightToCity from city 0, the source ##########

  flightToCity.push_back(nullFlight);// Flight from city 0 to city 0 is always a nullFlight.

  Flight flightWithEarliestPossibleArrival;
  Time timeFromSourceCity("12:00am");
  for (int i = 1; i < numberOfVertices; i++)
  {
    // FEWEST HOPS: flightThatGetsMeThere
    flightWithEarliestPossibleArrival = (*this).returnFlightWithEarliestPossibleArrival(cityNamesByIndex[0], cityNamesByIndex[i], timeFromSourceCity);
    flightToCity.push_back(flightWithEarliestPossibleArrival);       
  }

  if (debugModeOn)
  {
    cout << "Before call to oneDijkstraPass, the vector flightToCity holds:" << endl;
    for (int i = 0; i < numberOfVertices; i++)
    {
      flightToCity[i].show();
    }
  }// end if debug.

  // ########################### Set WEIGHTs of edges from city 0 ###########################

  int weightToCity[numberOfVertices];
  for (int i = 0; i < numberOfVertices; i++)
  {
    if (flightToCity[i].returnCityTo() == "NULL")
    {
      // ... there is no flight to city i, so set the weight to -1 (infinity).
      weightToCity[i] = -1;
    }
    else
    {
      // ... there is a flight to city i, so set the weight to the flight's time duration.
      weightToCity[i] = flightToCity[i].returnDuration();
      // FEWEST HOPS: weightToCity[i] = 1
    }
  }// end for i loop.

  if (debugModeOn)
  {
    for (int i = 0; i < numberOfVertices; i++)
    {
      cout << "Before call to oneDijkstraPass, weight from source city " << cityNamesByIndex[0] << " to " << cityNamesByIndex[i] << " = " << weightToCity[i] << endl;
    }
  }// end if debug.

  // Set DISTANCEs to vertices adjacent to vertex 0, the source ... and set their predecessor vertex to vertex 0:
  for (int i = 1; i < numberOfVertices; i++)
  {
    distToCity[i] = weightToCity[i];
  }

  // ################### Call function oneDijkstraPass (numberOfVertices - 1) times ###################

  for (int dijkIteration = 1; dijkIteration < numberOfVertices; dijkIteration++)
  {
    if (debugModeOn)
      cout << endl << "Dijkstra iteration #" << dijkIteration << ": *********************************************" << endl;

    oneDijkstraPass(numberOfVertices, negOneIfVertexInSetS, distToCity, flightToCity, cityNamesByIndex, searchOption);

    if (debugModeOn)
    {
      // Show cities along with their index numbers:
      for (int i = 0; i < numberOfVertices; i++)
      {
        cout << "cityNamesByIndex[" << i << "] = " << cityNamesByIndex[i] << endl;
      }
      cout << endl;

      // Show current distances to all vertices for each pass:
      for (int i = 0; i < numberOfVertices; i++)
      {
        if (distToCity[i] == -1)
          cout << "inf" << (char)9;
        else
          cout << distToCity[i] << (char)9;
      }
      cout << endl;

      // Show which vertices have already been visited:
      for (int i = 0; i < numberOfVertices; i++)
      {
        if (negOneIfVertexInSetS[i] == -1)
          cout << i << " in S" << (char)9;
        else
          cout << i << " in Q" << (char)9;
      }
      cout << endl;

      // Show flightToCity:
      for (int i = 0; i < numberOfVertices; i++)
      {
        cout << "flightToCity for city " << i << ": ";
        flightToCity[i].show();
      }
      cout << endl;

      // Show shortest path from source to destination:
      cout << "Here's the shortest path:" << endl;
      for (vector<Flight>::iterator iter = shortestPath.begin(); iter != shortestPath.end(); ++iter)
      {
        (*iter).show();
      }
      cout << endl;
    }// end if debug.
  }// end for dijkIteration loop.

  // ######## Assemble shortest path from source (vertex 0) to destination (vertex (numberOfVertices - 1)) ########

  // Make sure source city and destination city specified by user actually exist in the graph:
  int citySourceAsIndex = -1;
  int cityDestAsIndex = -1;
  for (int i = 0; i < numberOfVertices; i++)
  {
    if (cityNamesByIndex[i] == citySource)
      citySourceAsIndex = i;
    if (cityNamesByIndex[i] == cityDest)
      cityDestAsIndex = i;

  }// end for i loop.

  bool OkToReportshortestPath = true;
  if (citySourceAsIndex == -1)
  {
    OkToReportshortestPath = false;
    cout << "Sorry, the source city you've supplied isn't in our flight network." << endl;
  }
  if (cityDestAsIndex == -1)
  {
    OkToReportshortestPath = false;
    cout << "Sorry, the destination city you've supplied isn't in our flight network." << endl;
  }
  if (flightToCity[numberOfVertices - 1].returnCityFrom() == "NULL")
  {
    OkToReportshortestPath = false;
    cout << "Sorry, there is no itinerary that'll get you from the source city to the destination city." << endl;
  }

  if (OkToReportshortestPath)
  {
    vector<Flight>::iterator it;
    int cityToAsInt = numberOfVertices - 1;
    while (cityToAsInt != 0)
    {
      it = shortestPath.begin();
      it = shortestPath.insert(it, flightToCity[cityToAsInt]);

      for (int i = 0; i < numberOfVertices; i++)
      {
        if ( cityNamesByIndex[i] == flightToCity[cityToAsInt].returnCityFrom() )
          cityToAsInt = i;
      }
    }// end while (cityToAsInt != 0) loop.
  }// end if.

  return shortestPath;
}// end fn runDijkstraAlgorithm.


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%% fn oneDijkstraPass %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void Graph::oneDijkstraPass(int numberOfVertices, int *negOneIfVertexInSetS, int *dist, vector<Flight> &flightToCity, const vector<string> &cityNamesByIndex, const char &searchOption)
{
  bool debugModeOn = false;
  int minDistInSetQ = 9999999;// 9999999 = infinity.
  int vertexWithMinDistInSetQ = 0;// Preset vertexWithMinDistInSetQ as vertex 0 (the source vertex).

  Flight lastLegOfShortestDist;

  // ################# Identify the vertex still in Set Q with the shortest DIST #################

  for (int i = 0; i < numberOfVertices; i++)
  {
    if (negOneIfVertexInSetS[i] == -1)// Don't look at distances to cities already in S.
      continue;// Go to end of for i loop.
 
    if (dist[i] > 0 && dist[i] < minDistInSetQ)
    {
      minDistInSetQ = dist[i];
      vertexWithMinDistInSetQ = i;
      lastLegOfShortestDist = flightToCity[i];
    }
  }// end for i loop.

  // ===> vertex with shortest path in Set Q gets put into Set S:
  negOneIfVertexInSetS[vertexWithMinDistInSetQ] = -1;

  // ################# Get edges (flights) out of vertexWithMinDistInSetQ  #######################

  Time timeArrivalPreceedingFlight = lastLegOfShortestDist.returnTimeToAsObject();
  Flight nullFlight("NULL", "NULL", "12:00am", "11:59pm", "$999999");
  Flight flWithEarliestPossArr;

  // ############### Build vector flightFromMinInQueueTo for vertexWithMinDistInSetQ #############

  vector<Flight> flightFromMinInQueueTo;
  for (int i = 0; i < numberOfVertices; i++)
  {
    if (i == vertexWithMinDistInSetQ || negOneIfVertexInSetS[i] == -1)
    {// ... assign nullFlights to flights headed for cities already in/destined for Set S.
      flightFromMinInQueueTo.push_back(nullFlight);
    }
    else
    {// ... get edges on the fly that best connect with the arrival time of proceeding flight.
      flWithEarliestPossArr = (*this).returnFlightWithEarliestPossibleArrival(cityNamesByIndex[vertexWithMinDistInSetQ], cityNamesByIndex[i], timeArrivalPreceedingFlight);
      flightFromMinInQueueTo.push_back(flWithEarliestPossArr);
    }       
  }// end for i loop.

  // ##################################### Determine weights #####################################

  // Set WEIGHTs of edges from the city that's the vertexWithMinDistInSetQ:
  int weightToCity[numberOfVertices];
  for (int i = 0; i < numberOfVertices; i++)
  {
    if (flightFromMinInQueueTo[i].returnCityTo() == "NULL")
    {// ... there is no flight to city i, so set the weight to -1 (infinity).
      weightToCity[i] = -1;
    }
    else
    {// ... there is a flight to city i.
      weightToCity[i] = flightFromMinInQueueTo[i].returnTimestampTo() - lastLegOfShortestDist.returnTimestampTo();
    }
  }// end for i loop.

  if (debugModeOn)
  {
    for (int i = 0; i < numberOfVertices; i++)
    {
      cout << "In oneDijkstraPass, Flight weight from " << cityNamesByIndex[vertexWithMinDistInSetQ] <<" to " << cityNamesByIndex[i] << " = " << weightToCity[i] << ": "<<lastLegOfShortestDist.returnTimeTo()<<"-"<< flightFromMinInQueueTo[i].returnTimeTo()<< endl;
    }
    cout << endl;
  }// end if debugModeOn.

  // ############################### Get new DISTs using relaxation ##############################

  for (int i = 0; i < numberOfVertices; i++)
  {
    if (weightToCity[i] < 0)
      continue;// Go to end of for i loop since this vertex is not adjacent.

    // Relax ... if the distance to vertex i is currently inifinity (infinity being -1):
    if (dist[i] < 0)
    {
      dist[i] = minDistInSetQ + weightToCity[i];
      flightToCity[i] = flightFromMinInQueueTo[i];
      continue;// Go to end of for i loop.
    }

    // Relax ... if (distance to vertex i) > (shortest path left in Set Q) + (weight of the edge headed to vertex i):
    if ((dist[vertexWithMinDistInSetQ] + weightToCity[i]) < dist[i])
    {
      dist[i] = minDistInSetQ + weightToCity[i];
      flightToCity[i] = flightFromMinInQueueTo[i];
    }
  }// end for i loop.
}// end fn oneDijkstraPass
