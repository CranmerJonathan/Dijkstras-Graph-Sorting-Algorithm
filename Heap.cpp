//Name: Jonathan Cranmer & ASU ID: 1221599600

#include "Heap.h"
#include <iostream>

using std::cout;
using std::endl;

//Heap Constructor
Heap :: Heap(int capacity){
    this->size = 0;
    this->vertexes = new VERTEX*[capacity+1];
}

//Heap Destructor
Heap :: ~Heap(){
    delete[] vertexes;
}

//returns vertexes array
VERTEX** Heap :: getVertexes(){
    return vertexes;
}

//returns parent of index
int Heap :: parent(int i){
    return i/2;
}

//returns left child of index
int Heap :: left(int i){
    return i*2;
}

int Heap :: right(int i){
    return (i*2)+1;
}

//Decrease the d value of a vertex and reorganizes the heap
void Heap :: decreaseKey(int i, float key){
    if(key > vertexes[i]->d){
        cout << "nah";
    }
    else{
        vertexes[i]->d = key;
        while(i > 1 && vertexes[parent(i)]->d > vertexes[i]->d){
            int temp = vertexes[i]->index;
            vertexes[i]->index = vertexes[parent(i)]->index;
            vertexes[parent(i)]->index = temp;
            VERTEX* vertexTemp = vertexes[i];
            vertexes[i] = vertexes[parent(i)];
            vertexes[parent(i)] = vertexTemp;
            i = parent(i);
        }
    }
}

//inserts a vertex into the heap
void Heap :: insert(VERTEX* u, float key){
    size++;
    int i = size;
    u->index = size;
    u->d = 2147483647;
    vertexes[i] = u;
    decreaseKey(i, key);
}

//Prints vertexes used for debugging
void Heap :: printVertex(){
    if(vertexes != NULL){
        for(int i = 1; i <= size; i++){
        cout << "VERTEX: " << vertexes[i]->vertexName << " Value: " << vertexes[i]->d << endl;;
        if(vertexes[i]->pi != NULL){
            cout << "Pi: " << vertexes[i]->pi->vertexName << endl;
        }
        cout << endl;
        cout << endl;
        }
    }
}

//checks the heap to make sure it follows a minheap organization
void Heap :: minHeapify(int i, VERTEX** &arr){
    int l = left(i);
    int r = right(i);
    int smallest;
    int temp;
    VERTEX* vertexTemp;

    if(l <= size && arr[l]->d < arr[i]->d){
        smallest = l;
    }
    else{
        smallest = i;
    }
    if(r <= size && arr[r]->d < arr[smallest]->d){
        smallest = r;
    }

    if(smallest != i){

        VERTEX* temp = arr[smallest];
        VERTEX* temp2 = arr[i];
        temp->index = i;
        temp2->index = smallest;
        arr[i] = temp;
        arr[smallest] = temp2;
        minHeapify(smallest, arr);
    }
}

//Extracts the first node of the index
VERTEX* Heap :: extractMin(){
    if(size < 1){
        cout << "bruh" << endl;
        return NULL;
    }
    else {
        VERTEX* min = vertexes[1];
        VERTEX* last = vertexes[size];
        last->index = 1;
        min->index = size;
        vertexes[size] = min;
        vertexes[1] = last;
        size--;

        VERTEX** arr = vertexes;

        minHeapify(1, arr);
        vertexes = arr;
        return min;
    }
}

//return heaps size
int Heap :: getSize(){
    return size;
}