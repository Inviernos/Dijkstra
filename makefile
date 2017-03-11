Path: Main.o Graph.o
	g++ Main.o Graph.o -o Path
Main.o: Main.cpp Graph.h
	g++ -c Main.cpp
Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp
clean: 
	rm -f *.o
remove:
	rm -f * Path
removeall:
	rm -f *.o
	rm -f Path
	ls