Program3
========
Responsibilites:

George Metzger:
       Working on the Date and Time class for efficient and useful storage of those things.
       Finding the Shortest Travel Time. 

Leonid Mamut:
       Building of the Graph.
       Finding the Fewest Hops.

Denis Plotkin:
      Dealing with input and manipulation thereof.
      Building the proper classes to store objects such as a city, a flight, etc.
      Setting up git repository, resolving logistics to make working streamlined.
      Just Get Me There.

Description of Algorithms

Finding the Shortest Travel Time - We’ll use Dijkstra's Algorithm here. 
We will have to select one flight for each leg of the itinerary as the 
algorithm progresses from the source towards the final destination. 
(Dijkstra's Algorithm doesn’t know how to cope with multiple edges 
between two nodes.) The selected flight will be the one that departs 
after the predecessor flight arrives--yet also gets us to the second 
city at the earliest possible time.

Finding the Fewest Hops - We’ve already got a handle on Dijkstra's 
Algorithm, so why not use it again? Here, we will arbitrarily use the 
earliest flight for each leg (as we needn’t worry about limiting the 
itinerary to a single day), but we’ll also set the time duration of each 
leg to the same value. Now that the weights of all the edges are equal, 
the algorithm will yield the itinerary with the fewest legs.

Just Get Me There - It’s Dijkstra's Algorithm, again, but this time we’ll 
quit as soon as the algorithm calculates the first non-infinity value for 
dist[destination city]. In other words, we quit the routine without 
looking to do any further relaxation--once we find a complete path to 
the destination, we are done.

Finding the Cheapest - This search option poses a tricky problem. 
Dijkstra's algorithm won’t cut it because it is 'greedy': It opts for the 
lowest weight edge from the word go. The problem here is that it'll feed 
you the cheapest edge for the first leg of the itinerary, for instance, 
but that first flight may leave later in the day, preventing you from 
connecting to another leg that would save you even more cash. We shall 
either try a non-greedy algorithm here, such as Bellman-Ford, or use 
brute force to find every possible itinerary … and then choose the 
cheapest one that unfolds  within the scope of a day.


Timeline:
November 22nd: Met up to establish our workflow, including setting up a git repository and figuring out what data structures we would use, specifically in regards to working on Lab 8.
Sunday (12/7): Have algorithims finished. Decide, based on if this is accomplished, whether to pursue the extra credit or work on the core requirements first.
Monday (12/8): Meetup after class to plan for presentation as well as to work on whatever we couldn't finish on our own.
Tuesday (12/9): Presentation in lab


Design:

Our design consists of a two tiered vector structure. At the top layer, we have a vector of City objects. When we read in the information from the DDFS file, we build up this vector, constructing a new city based on the origin city. We also check if the destination city is in the vector; if it isn't, we add it as well. Each city is only added once. After the city is added (or if it was already in there), we add a flight to the city. This consists of adding a Flight object to the vector within the city class. A flight consists of all the information on the line in the DDFS file and is the "edge" in our graph, and the city is the vertex. 
