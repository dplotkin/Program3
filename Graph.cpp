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
  Flight flightWithEarliestPossibleArrival("NULL", "NULL", "12:00am", "11:59pm", "$999999");

  for(int i = 0; i < cities.size(); i++)//.size() = total number of flights
  {
    if (cities[i].getName() == cityFrom)
    {
      for(int j = 0; j < cities[i].getFlights().size(); j++)// j = index of flight in flights vector.
      {// Loop through flights leaving the city cities[i].
        if (cities[i].getFlights()[j].returnCityTo() == cityTo && cities[i].getFlights()[j].returnTimeFrom() >= earliestPossibleTimeFrom)
        {// ... the flight goes to the city specified, and it leaves after the predecessor flight arrives.
          //cout <<endl<< "flightWithEarliestPossibleArrival.returnTimeTo() = "<< flightWithEarliestPossibleArrival.returnTimeTo() <<":" <<endl;
          //cout << "flightWithEarliestPossibleArrival.returnTimestampTo() = "<< flightWithEarliestPossibleArrival.returnTimestampTo() <<":" <<endl;
          //flightWithEarliestPossibleArrival.show();

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

void Graph::runDijkstraAlgorithm(const string &citySource, const string &cityDest)
{
  vector<string> cityNamesByIndex;
  vector<Flight> shortestPath;

  int numberOfVertices = cities.size();

  // Put all cities into vector cityNamesByIndex:
  for(int i = 0; i < numberOfVertices; i++)
  {
    cityNamesByIndex.push_back( cities[i].getName() );
  }

  // Put SOURCE city into cityNamesByIndex[0] and DESTINATION city into cityNamesByIndex[cities.size() - 1]:
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
/*  
  for (int i = 0; i < cityNamesByIndex.size(); i++)
  {
    cout << "Hey, cityNamesByIndex[i] = " << cityNamesByIndex[i] << endl;
  }

*/

  int negOneIfVertexInSetS[numberOfVertices];
  int distToCity[numberOfVertices];
  //int predecessorVertexTo[numberOfVertices];

  // all vertices start in Set Q:
  for (int i = 0; i < numberOfVertices; i++)
  {
    // When vertex is still in Q, negOneIfVertexInSetS[i] is positive:
    negOneIfVertexInSetS[i] = i;
  }

  // Put our source vertex 0 in Set S and make dist[0] zero:
  negOneIfVertexInSetS[0] = -1;
  distToCity[0] = 0;

/*  // Preset the predecessor vertex to each vertex to 0:
  for (int i = 0; i < numberOfVertices; i++)
  { 
    // When we don't know the predecessor vertex, we'll say it's vertex 0:
    predecessorVertexTo[i] = 0; 
  }*/

  cout << "cityNamesByIndex[0] = " << cityNamesByIndex[0] << endl;

  // Vector relevantFlightsOut contains flights out from the city presently being visited by Dijkstra's 
  // Algorithm. There is one relevant flight (the one arrving earliest, for instance) to each city.
  // If there is no flight to that particular city, then a dummy nullFlight is scheduled to that city.
  vector<Flight> relevantFlightsOut;
  Flight nullFlight("NULL", "NULL", "12:00am", "11:59pm", "$999999");

  // Populate vector relevantFlightsOut from city 0, the source:
  relevantFlightsOut.push_back(nullFlight);// Flight from city 0 to city 0 is always a nullFlight.

  Flight flightWithEarliestPossibleArrival;
  Time timeFromSourceCity("12:00am");
  for (int i = 1; i < numberOfVertices; i++)
  {
    flightWithEarliestPossibleArrival = (*this).returnFlightWithEarliestPossibleArrival(cityNamesByIndex[0], cityNamesByIndex[i], timeFromSourceCity);
    relevantFlightsOut.push_back(flightWithEarliestPossibleArrival);       
  }

/*  cout << "^flights out from city 0: " << endl;
  for (int i = 0; i < numberOfVertices; i++)
  {
    cout << "Flight from source city " << cityNamesByIndex[0] << " to " << cityNamesByIndex[i] << ": ";
    relevantFlightsOut[i].show();
  }*/

  int weightToCity[numberOfVertices];
  // Set WEIGHTs of edges from city 0:
  for (int i = 0; i < numberOfVertices; i++)
  {
    if (relevantFlightsOut[i].returnCityTo() == "NULL")
    {
      // ... there is no flight to city i, so set the weight to -1 (infinity).
      weightToCity[i] = -1;
    }
    else
    {
      // ... there is a flight to city i, so set the weight to the flight's time duration.
      weightToCity[i] = relevantFlightsOut[i].returnDuration();
    }
  }// end for i loop.

  for (int i = 0; i < numberOfVertices; i++)
  {
    cout << "Flight duration from source city " << cityNamesByIndex[0] << " to " << cityNamesByIndex[i] << " = " << weightToCity[i] << endl;
  }

  // Set DISTANCEs to vertices adjacent to vertex 0, the source ... and set their predecessor vertex to vertex 0:
  for (int i = 1; i < numberOfVertices; i++)
  {
    distToCity[i] = weightToCity[i];
  }

  // Call function oneDijkstraPass (numberOfVertices - 1) times:
  Flight shortestFlight;
  for (int dijkIteration = 1; dijkIteration < numberOfVertices; dijkIteration++)
  {
    shortestFlight = oneDijkstraPass(negOneIfVertexInSetS, distToCity, relevantFlightsOut, cityNamesByIndex /*predecessorVertexTo/*, weightToCity*/);
    shortestPath.push_back(shortestFlight);

    cout << "Dijkstra iteration #" << dijkIteration << ":" << endl;

    // Show current distances to all vertices for each pass:
    for (int i = 0; i < numberOfVertices; i++)
    {
      if (distToCity[i] == -1)
        cout << "dist[" << i << "] = inf" << (char)9;
      else
        cout << "dist[" << i << "] = " << distToCity[i] << (char)9;
    }
    cout << endl;

    // Show which vertices have already been visited:
    for (int i = 0; i < numberOfVertices; i++)
    {
      if (negOneIfVertexInSetS[i] == -1)
        cout << "vrtx " << i << " in S" << (char)9;
      else
        cout << "vrtx " << i << " in Q" << (char)9;
    }
    cout << endl;          

  }// end for dijkIteration loop.
}// end fn runDijkstraAlgorithm.


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%% fn oneDijkstraPass %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//void oneDijkstraPass(int *negOneIfVertexInSetS, int *dist, int *predecessorVertexTo/*, int weight[numberOfVertices][numberOfVertices]*/)
Flight Graph::oneDijkstraPass(int *negOneIfVertexInSetS, int *dist, vector<Flight> &relevantFlightsOut, const vector<string> &cityNamesByIndex /*int *predecessorVertexTo, int *weight*/)
{
  int minDistInSetQ = 32767;// 32767 = infinity, I guess.
  int vertexWithMinDistInSetQ = 0;// Preset vertexWithMinDistInSetQ as vertex 0 (the source vertex).
  Flight shortestFlight;

  int numberOfVertices = sizeof(negOneIfVertexInSetS);

  // ################# Identify the vertex still in Set Q with the shortest path #################

  for (int i = 0; i < numberOfVertices; i++)
  {
    if (negOneIfVertexInSetS[i] == -1)
      continue;// Go to end of for i loop.

    if (dist[i] > 0 && dist[i] < minDistInSetQ)
    {
      minDistInSetQ = dist[i];
      vertexWithMinDistInSetQ = i;
      shortestFlight = relevantFlightsOut[i];
    }
  }// end for i loop.

  cout << "   Obtain all vertices from vertex " << vertexWithMinDistInSetQ << " here, because ..." << endl;   

  // Vertex with shortest path in Set Q gets put into Set S:
  negOneIfVertexInSetS[vertexWithMinDistInSetQ] = -1;

  relevantFlightsOut.clear();

  // ############################## Determine weights ##############################

  Time timeArrivalPreceedingFlight = shortestFlight.returnTimeToAsObject();
  Flight nullFlight("NULL", "NULL", "12:00am", "11:59pm", "$999999");
  Flight flWithEarliestPossArr;

  // ########## Remake vector relevantFlightsOut for vertexWithMinDistInSetQ #########
  for (int i = 0; i < numberOfVertices; i++)
  {
    if (i == vertexWithMinDistInSetQ || negOneIfVertexInSetS[i] == -1)
    {// ... assign nullFlights to flights headed for cities already in/destined for Set S.
      relevantFlightsOut.push_back(nullFlight);
    }
    else
    {// ... get edges on the fly that best connect with the arrival time of proceeding flight.
      flWithEarliestPossArr = (*this).returnFlightWithEarliestPossibleArrival(cityNamesByIndex[vertexWithMinDistInSetQ], cityNamesByIndex[i], timeArrivalPreceedingFlight);
      relevantFlightsOut.push_back(flWithEarliestPossArr);
    }       
  }// end for i loop.

  // Set WEIGHTs of edges from the city that's the vertexWithMinDistInSetQ:
  int weightToCity[numberOfVertices];
  for (int i = 0; i < numberOfVertices; i++)
  {
    //relevantFlightsOut[1].show();

    if (relevantFlightsOut[i].returnCityTo() == "NULL")
    {
      // ... there is no flight to city i, so set the weight to -1 (infinity).
      weightToCity[i] = -1;
    }

    else
    {
      // ... there is a flight to city i, so set the weight to the flight's time duration.
      weightToCity[i] = relevantFlightsOut[i].returnDuration();
    }
  }// end for i loop.

  // ################################ Get new DISTs using relaxation ################################

  for (int i = 0; i < numberOfVertices; i++)
  {
    if (weightToCity[i] < 0)
      continue;// Go to end of for i loop since this vertex is not adjacent.

    // Relax ... if the distance to vertex i is currently inifinity (infinity being -1):
    if (dist[i] < 0)
    {
      dist[i] = minDistInSetQ + weightToCity[i];
      //predecessorVertexTo[i] = vertexWithMinDistInSetQ;
      continue;// Go to end of for i loop.
    }

    // Relax ... if (distance to vertex i) > (shortest path left in Set Q) + (weight of the edge headed to vertex i):
    if ((dist[vertexWithMinDistInSetQ] + weightToCity[i]) < dist[i])
    {
      dist[i] = minDistInSetQ + weightToCity[i];
      //predecessorVertexTo[i] = vertexWithMinDistInSetQ;
    }
  }// end for i loop.

  return shortestFlight;
}// end fn oneDijkstraPass

int Graph::shortestPath(int start, int destination){
int n = cities.size(); 
vector<int> distLabel(n, -1), predLabel(n);
distLabel[start] = 0;
int distance = 0, vertex;
queue <int> vertexQueue;
vertexQueue.push(start);
while(distLabel[destination] < 0 && !vertexQueue.empty()){
vertex = vertexQueue.front();
vertexQueue.pop();
if(distLabel[vertex] > distance){
distance++;
}
/*for(vector<int>::iterator it = cities.begin(); it != cities.end(); it++){
if(distLabel[*it] < 0){
distLabel[*it] = distance + 1;
predLabel[*it] = vertex;
vertexQueue.push(*it);
}
*/
}
distance++;
}


