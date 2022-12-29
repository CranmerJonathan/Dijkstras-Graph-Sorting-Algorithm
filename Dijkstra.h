//Name: Jonathan Cranmer & ASU ID: 1221599600

#include "Heap.h"

class Dijkstra{
  private:
    VERTEX** G;
    VERTEX** S;
    int size;
    VERTEX* source;
    Heap* minHeap;
  public:
    Dijkstra(VERTEX**, VERTEX*, int);
    Dijkstra(VERTEX**, VERTEX*, VERTEX*,int);
    ~Dijkstra();
    void initializeSingleSource();
    void Relax(VERTEX*, VERTEX*, float);
    void stopWarning();
};