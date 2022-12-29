//Name: Jonathan Cranmer & ASU ID: 1221599600

#include "Dijkstra.h"
#include <iostream>

using std::cout;
using std::endl;

//Constructor class that runs Dijkstras algorithm
Dijkstra :: Dijkstra(VERTEX** G, VERTEX* source, int size){
    this->source = source;
    this->G = G;
    this->size = size;
    ADJLIST* adjListTemp;
    initializeSingleSource();
    S = new VERTEX*[size+1];
    minHeap = new Heap(size);
    int j = 1;
    for(int i = 1; i <= size; i++){
      minHeap->insert(this->G[i], this->G[i]->d);
    }
    while(minHeap->getSize() != 0){
      S[j] = minHeap->extractMin();
      adjListTemp = S[j]->adjList;
      while(adjListTemp != NULL){
          Relax(adjListTemp->u, adjListTemp->v, adjListTemp->w);
          adjListTemp = adjListTemp->adjList;
      }
      j++;
    }
}

//Constructor Override that runs Dijkstras algorithm with a source and destination
Dijkstra :: Dijkstra(VERTEX** G, VERTEX* source, VERTEX* destination, int size){
    this->source = source;
    this->G = G;
    this->size = size;
    ADJLIST* adjListTemp;
    initializeSingleSource();
    S = new VERTEX*[size+1];
    minHeap = new Heap(size);
    int j = 1;
    for(int i = 1; i <= size; i++){
        minHeap->insert(this->G[i], this->G[i]->d);
    }
    while(minHeap->getSize() != 0){
        S[j] = minHeap->extractMin();
        if(S[j] == destination){
            break;
        }
        adjListTemp = S[j]->adjList;
        while(adjListTemp != NULL){
            Relax(adjListTemp->u, adjListTemp->v, adjListTemp->w);
            adjListTemp = adjListTemp->adjList;
        }
        j++;
    }
}

//Dijkstras Destructor
Dijkstra :: ~Dijkstra(){
    delete[] S;
    delete minHeap;
}

//InitializesSingleSource algoirthm
void Dijkstra :: initializeSingleSource(){
  for(int i = 1; i <= size; i++){
        G[i]->d = 2147483647;
        G[i]->pi = NULL;
    }
   source->d = 0.0;
}

//relax algorithm
void Dijkstra :: Relax(VERTEX* u, VERTEX* v, float w){
    if(v->d > (u->d + w)){
        minHeap->decreaseKey(v->index, (float)(u->d + w));
        v->pi = u;
    }
}

//used to stop console warning
void Dijkstra :: stopWarning(){

}
