all: Flight

Flight: driver.o Graph.o
	g++ driver.o Graph.o -o Flight

driver.o: driver.cpp
	g++ -c driver.cpp -o driver.o

Graph.o: Graph.cpp
	g++ -c Graph.cpp -o Graph.o

clean:
	rm -f *.o Flight
