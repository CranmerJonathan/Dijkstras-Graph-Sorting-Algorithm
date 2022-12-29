//Name: Jonathan Cranmer & ASU ID: 1221599600

#include "Dijkstra.h"

class Util
    {
      private:
        VERTEX** vertexes;
        VERTEX** vertexHeap;
        int numVertex;
        int numEdge;
        char* fileName;
        char* directedCheck;

        void printAdjList();
        void readFile();
        void userInteraction();
        void printVertexes();
        void singlePair(int, int);
        void singleSource(int);
        void printPath(int, int);
        void printLength(int, int);
        void printVertexesHeap();
      public:
        Util(char*, char*);
        ~Util();
    };