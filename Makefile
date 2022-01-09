.PHONY: clean all
CC = gcc
AR = ar
FLAGS= -Wall -g

all: graph

graph: main.o graph.a
	$(CC) $(FLAGS) -o graph main.o graph.a
graph.a: graph.o Dijkstra.o tsp.o
	$(AR) -rcs graph.a graph.o Dijkstra.o tsp.o
main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c
graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c
Dijkstra.o: Dijkstra.c graph.h
	$(CC) $(FLAGS) -c Dijkstra.c
tsp.o: TSP.c graph.h
	$(CC) $(FLAGS) -c TSP.c
clean:
	rm -f *.o *.so graph