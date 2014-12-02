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
  
  //User-provided information
  
  string departure;
  string destination;
  string departureDate;
  string earliestDepartureTime;
  string returnDate;
  string earliestReturnTime;
  string customerObjective;

  cout << "Please enter your departure city." << endl;
  cin >> departure;
  cout << "Please enter your destination city." << endl;
  cin >> destination;
  cout << "Please enter your departure date." << endl;
  cin >> departureDate;
  cout << "Please enter your earliest acceptable departure time." << endl;
  cin >> earliestDepartureTime;
  cout << "Please enter your return date." << endl;
  cin >> returnDate;
  cout << "Please enter your earliest acceptable return time." << endl;
  cin >> earliestReturnTime;
  cout << "Thank you." << endl << "------------------------" << endl;
  cout << "Please specify which Customer Objective is preferable for your itinerary:" << endl;
  cout << "\tJ: Just Get Me There: Find any itinerary that will get the customer from the departure city to the destination city, and back again, regardless of the number of flights, the cost, or the travel time." << endl;
  cout << "\tF: Fewest Hops: Find the itinerary that can meet the constraints with the fewest individual direct flight components." << endl;
  cout << "\tS: Shortest Trip: Find the itinerary that will minimize the time between leaving from the departure city, and arriving at the destination city… and will also minimize the time between starting the return from the destination city and arriving back at the departure city on the return date." << endl;
  cout << "\tC: Cheapest: Find the cheapest (potentially multi-hop) itinerary, in terms of dollars, that meets the trip constraints." << endl;
  cout << "\tP: Print: Print out the Daily Flight Schedule." << endl;
  cin >> customerObjective;
  if(customerObjective == "J"){
    cout << "We are sorry, this option is not yet implemented. Have a nice day!" << endl;
  }
  else if(customerObjective == "F"){
    cout << "We are sorry, this option is not yet implemented. Have a nice day!" << endl;
  }
  else if(customerObjective == "C"){
    cout << "We are sorry, this option is not yet implemented. Have a nice day!" << endl;
  }
  else if(customerObjective == "S"){
    cout << "We are sorry, this option is not yet implemented. Have a nice day!" << endl;
  }
  else if(customerObjective == "P"){
    //Prints out the flights that are available. I.e. reads the information from the DDFS from our data structure
  }
  
  
  
}
