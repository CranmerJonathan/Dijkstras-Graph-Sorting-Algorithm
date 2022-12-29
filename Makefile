EXEC = PJ3
CC = g++
CFLAGS = -c -Wall
#
$(EXEC) :main.o Util.o Heap.o Dijkstra.o
	$(CC) -o $(EXEC) main.o Util.o Heap.o Dijkstra.o
#
main.o	:main.cpp Util.h Heap.h Dijkstra.h
	$(CC) $(CFLAGS) main.cpp
# 
MinHeap.o	:Heap.cpp Heap.h 
	$(CC) $(CFLAGS) Heap.cpp
#
Util.o	:Util.cpp Util.h Heap.h Dijkstra.h
	$(CC) $(CFLAGS) Util.cpp
#
Dijkstra.o	:Dijkstra.cpp Dijkstra.h Heap.h
	$(CC) $(CFLAGS) Dijkstra.cpp
#