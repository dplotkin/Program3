Program3
========
Responsibilites:

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

Write-Ups:
Fewest Hops: The Fewest Hops Algorithim will be use a shortest-path 
algorithim. We will use Dijkstra's algorithim to solve this problem. 
The weight of each edge will be 1 though, so the fewest hops can be 
stored and using the earliest possible edge. Dijkstra's algorithim will 
produce a shortest path graph. 

Timeline:
Sunday (12/7): Have algorithims finished?
Monday (12/8): Meetup after class to plan for presentation.
Tusday (12/9): Presentation in lab
