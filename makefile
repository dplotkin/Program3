all: Flight

Flight: driver.o Graph.o Flight.o
	g++ -std=c++11 driver.o Graph.o -o Flight

driver.o: driver.cpp
	g++ -std=c++11 -c driver.cpp -o driver.o

Graph.o: Graph.cpp
	g++ -std=c++11 -c Graph.cpp -o Graph.o

Flight.o: Flight.cpp
	g++ -std=c++11 -c Flight.cpp -o Flight.o

clean:
	rm -f *.o Flight

git: clean
	git add -A;
	git commit -m "automated git usage";
	git pull;
	git push;
