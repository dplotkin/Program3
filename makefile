all: Flight

Flight: driver.o Graph.o Flight.o Time.o Date.o City.o
	g++ -std=c++11 driver.o Graph.o Flight.o Time.o Date.o City.o -o Flight

driver.o: driver.cpp
	g++ -std=c++11 -c driver.cpp -o driver.o

Graph.o: Graph.cpp
	g++ -std=c++11 -c Graph.cpp -o Graph.o

Flight.o: Flight.cpp
	g++ -std=c++11 -c Flight.cpp -o Flight.o

Time.o: Time.cpp
	g++ -std=c++11 -c Time.cpp -o Time.o

Date.o: Date.cpp
	g++ -std=c++11 -c Date.cpp -o Date.o

City.o: City.cpp
	g++ -std=c++11 -c City.cpp -o City.o

clean:
	rm -f *.o Flight

git: clean
	git add -A;
	git commit -m "automated git usage";
	git pull;
	git push;
