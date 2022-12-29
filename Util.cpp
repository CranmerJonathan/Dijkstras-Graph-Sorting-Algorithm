//Name: Jonathan Cranmer & ASU ID: 1221599600

//including stuff
#include "Util.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

//using Std
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::setw;
using std::setprecision;
using std::fixed;

//Util Declaration
Util :: Util(char* directedCheck, char* fileName){          //first char pointer determines if directedcheck or not second char pointer is the file name
    this->fileName = fileName;                              //assigning file name
    this->directedCheck = directedCheck;                    //assigning directed check
    this->vertexes = NULL;                                  //declaring vertexes as null so readFile() can assign it

    readFile();                                             //reads from file and creates adjlist and vertexes
    userInteraction();                                      //interacts with the user
}

Util :: ~Util(){                                            //Destructor class
    ADJLIST* adjlistTemp;                                   //temperary adjlist used for deletion

    //give memory back make sure to check for no memory leaks in general and everything works righ
    if(vertexes != NULL){                                   //if vertexes is empty don't run any of the deletion
        for(int i = 1; i <=numVertex; i++){                 //loop through all of the vertexes
                if(vertexes[i] != NULL){                    //if the vertex pointer is null don't run this
                    adjlistTemp = vertexes[i]->adjList;     //assign adjlisttemp to be the first adjlist in the adjlist of a vertex (used for deletion)
                    while(adjlistTemp != NULL){             //if adjlist empty dont run
                        vertexes[i]->adjList = vertexes[i]->adjList->adjList;   //move one over in the adjlist linked list 
                        delete adjlistTemp;                 //delete first adjlist in the linked list
                        adjlistTemp = vertexes[i]->adjList; //move the second node into adjlisttemp (used for deletion)
                    }
                    vertexes[i] = NULL;                     //set the vertex = NULL clearing the data
                    delete vertexes[i];                     //delete the vertex
                }
            }
        delete[] vertexes;                                  //delete array of vertexes
    }
}

void Util :: userInteraction(){                             //function to interact with the user
    int cont = 1, temp1, temp2, source = 0, destination = 0, pairPath = 0, sourcePath = 0; 
    //cont=continue or not used for stop command temp1 is source temp 2 is destination source 
    //saves source after singlepair or singlesource are ran and destination saves destination 
    //if singlepair is ran pair path saves if singlepath was used and sourcePath saves if singleSource was used
    char userInput[50];                                     //userInput saves what the user inputs

    //Keep interacting with the user until Stop is submitted
    while(cont == 1)   {                                    //while continue is 1 keep looking for more commands
        scanf("%s", userInput);                             //scans user input
        //Stop
        if(strcmp(userInput, "Stop") == 0){                 //stops if stop is submitted
            cont = 0;                                       //sets cont to be zero so function ends
        } 
        //SinglePair <source> <destination>
        else if(strcmp(userInput, "SinglePair" ) == 0){     //singlepair saves source and destination and runs graphAlg to solve for the path
            scanf("%d", &source);                           //scans the source vertex
            scanf("%d", &destination);                      //scans for the destination index
            pairPath = 1;                                   //pairpath = 1 since single pair was just ran
            sourcePath = 0;                                 //sourcepath = 0 since single pair is ran
            singlePair(source, destination);                //function to execute singlepair 
        }
        //SingleSource <source>
        else if(strcmp(userInput, "SingleSource") == 0){    //single source saves source and runs graphAlg to find shortest path thing
            scanf("%d", &source);                           //scan for source
            sourcePath = 1;                                 //sourcepath = 1 since single source was just ran
            pairPath = 0;                                   //pairpath = 0 since single source is ran
            singleSource(source);                           //function to execute singleSource
        }
        //PrintPath <s> <t>
        else if(strcmp(userInput, "PrintPath" ) == 0){      //printPath if source = temp1 and destination = temp2
            scanf("%d", &temp1);                            //gets source attempt from user and stores in temp1
            scanf("%d", &temp2);                            //gets destination attempt from user and stores in temp2
            //checks if source= temp1 and destination = temp2
            if((pairPath == 1 && temp1 == source && temp2 == destination) || (sourcePath == 1 && temp1 == source)){
                printPath(temp1, temp2);                    //function the runs printPath
            }
            else{                                           //else
                cerr << "Error: Invalid command" << endl;   //output error
            }
        }
        //PrintLength <s> <t>
        else if(strcmp(userInput, "PrintLength") == 0){     //if user input is print legnth and source and destination are right print the length
            scanf("%d", &temp1);                            //temp1 = source attempt
            scanf("%d", &temp2);                            //temp2 = destination attempt
            //checks if temp1 = source and temp2 = destination
            if((pairPath == 1 && temp1 == source && temp2 == destination) || (sourcePath == 1 && temp1 == source)){
                printLength(temp1, temp2);
            }
            else{                                           //else
                cerr << "Error: Invalid command" << endl;   //output error
            }
        }
        //PrintADJ
        else if(strcmp(userInput, "PrintADJ") == 0){    //if user input is printADJ printADJ
            printAdjList();                             //function to printADJ
        }
        //Incorrect input
        else
        {
            cerr << "Error: Invalid command" << endl;   //output error if invalid command
        }
    }  
    return;
}

//printADJList command
void Util :: printAdjList(){
    ADJLIST* adjlistTemp;                               //used for temp stuff
    for(int i = 1; i <= numVertex; i++){                //loop through each vertex
        cout << "ADJ[" << vertexes[i]->vertexName << "]:";
        adjlistTemp = vertexes[i]->adjList;             //assign adjlisttemp to the first node in the linked list
        while(adjlistTemp != NULL){                     //if adjlisttemp isn't null we good
            //cout all the stuff
            cout << "-->[" << adjlistTemp->u->vertexName << " " << adjlistTemp->v->vertexName
                 << ": " << setprecision(2) << std::fixed << adjlistTemp->w << "]";
            adjlistTemp = adjlistTemp->adjList;         //assign adjlisttemp to the next node
        }
        cout << endl;                                   //new line after each vertex
    }
}

//Reads from file and creates vertexes and adjlists
void Util :: readFile(){
    int temp1, temp2, temp3, i, j;
    float temp4;
    ADJLIST* adjlistTemp;

    //opens file
    ifstream file;
    file.open(fileName);
    
    //create vertex array
    file >> numVertex;
    vertexes = new VERTEX*[numVertex + 1];

    //get numEdge from file
    file >> numEdge;

    //Directed Check
    if((strcmp("Directed", directedCheck) == 0)){
        //Create vertex pointers
        for(i = 1; i <= numVertex; i++){
            vertexes[i] = new VERTEX();
            vertexes[i]->adjList = NULL;
            vertexes[i]->vertexName = i;
            strcpy(vertexes[i]->color, "WHITE" );
            vertexes[i]->d = (float)2147483647;
            vertexes[i]->pi = NULL;
            vertexes[i]->position = -1;
            vertexes[i]->index = i;
        }

        //DELETE output edges from file(checking if reading file correctly)
        for(j = 0; j < numEdge; j++){
            file >> temp1;
            file >> temp2;
            file >> temp3;
            file >> temp4;

            if(vertexes[temp2]->adjList == NULL){
                vertexes[temp2]->adjList = new ADJLIST();
                vertexes[temp2]->adjList->index = temp1;
                vertexes[temp2]->adjList->u = vertexes[temp2];
                vertexes[temp2]->adjList->v = vertexes[temp3];
                vertexes[temp2]->adjList->w = (float)temp4;
                vertexes[temp2]->adjList->adjList = NULL;
            }
            else{
                adjlistTemp = vertexes[temp2]->adjList;
                vertexes[temp2]->adjList = new ADJLIST;
                vertexes[temp2]->adjList->index = temp1;
                vertexes[temp2]->adjList->u = vertexes[temp2];
                vertexes[temp2]->adjList->v = vertexes[temp3];
                vertexes[temp2]->adjList->w = (float)temp4;
                vertexes[temp2]->adjList->adjList = adjlistTemp;
            }
        }
        
    }

    //Undirected Check
    if((strcmp("Undirected", directedCheck) == 0)){
        //Create vertex pointers
        for(i = 1; i <= numVertex; i++){
            vertexes[i] = new VERTEX();
            vertexes[i]->adjList = NULL;
            vertexes[i]->vertexName = i;
            strcpy(vertexes[i]->color, "WHITE" );
            vertexes[i]->d = (float)2147483647;
            vertexes[i]->pi = NULL;
            vertexes[i]->position = -1;
            vertexes[i]->index = i;
        }

        //DELETE output edges from file(checking if reading file correctly)
        for(j = 0; j < numEdge; j++){
            file >> temp1;
            file >> temp2;
            file >> temp3;
            file >> temp4;

            if(vertexes[temp2]->adjList == NULL){
                vertexes[temp2]->adjList = new ADJLIST();
                vertexes[temp2]->adjList->index = temp1;
                vertexes[temp2]->adjList->u = vertexes[temp2];
                vertexes[temp2]->adjList->v = vertexes[temp3];
                vertexes[temp2]->adjList->w = (float)temp4;
                vertexes[temp2]->adjList->adjList = NULL;
            }
            else{
                adjlistTemp = vertexes[temp2]->adjList;
                vertexes[temp2]->adjList = new ADJLIST();
                vertexes[temp2]->adjList->index = temp1;
                vertexes[temp2]->adjList->u = vertexes[temp2];
                vertexes[temp2]->adjList->v = vertexes[temp3];
                vertexes[temp2]->adjList->w = (float)temp4;
                vertexes[temp2]->adjList->adjList = adjlistTemp;
            }

            if(vertexes[temp3]->adjList == NULL){
                vertexes[temp3]->adjList = new ADJLIST();
                vertexes[temp3]->adjList->index = temp1;
                vertexes[temp3]->adjList->u = vertexes[temp3];
                vertexes[temp3]->adjList->v = vertexes[temp2];
                vertexes[temp3]->adjList->w = (float)temp4;
                vertexes[temp3]->adjList->adjList = NULL;
            }
            else{
                adjlistTemp = vertexes[temp3]->adjList;
                vertexes[temp3]->adjList = new ADJLIST();
                vertexes[temp3]->adjList->index = temp1;
                vertexes[temp3]->adjList->u = vertexes[temp3];
                vertexes[temp3]->adjList->v = vertexes[temp2];
                vertexes[temp3]->adjList->w = (float)temp4;
                vertexes[temp3]->adjList->adjList = adjlistTemp;
            }
        }
        
    }

    file.close(); 
}

//runs dijkstras algorithm with a source and destination
void Util :: singlePair(int source, int destination){
    Dijkstra* graphAlg = new Dijkstra(vertexes, vertexes[source], vertexes[destination], numVertex);
    graphAlg->stopWarning();
    delete graphAlg;
}

//runs dijkstras algorithm with a source
void Util :: singleSource(int source){
  Dijkstra* graphAlg = new Dijkstra(vertexes, vertexes[source], numVertex);
  graphAlg->stopWarning();
  delete graphAlg;
}

//Prints the path between two points
void Util :: printPath(int source, int destination){
    if((vertexes[destination]->pi == NULL) && vertexes[destination] != vertexes[source]){
        cout << "There is no path from " << source << " to " << destination << "." <<endl;
        return;
    }
    if(vertexes[destination] == vertexes[source]){
        cout << fixed << "The shortest path from " << source << " to " << destination << " is:" << endl << "[8:    0.00]." << endl;
        return;
    }
    VERTEX* temp = vertexes[destination];
    int amountVertexes = 0;
    int* vertexesIndex = new int[numVertex + 1];
    
    while(temp != vertexes[source]){
        amountVertexes++;
        vertexesIndex[amountVertexes] = temp->vertexName;
        temp = temp->pi;
    }
    cout << fixed << "The shortest path from " << source << " to " << destination << " is:" << endl;
    cout << fixed << "[" << vertexes[source]->vertexName << ":" << setw(8) << setprecision(2) << (float)vertexes[source]->d << "]-->";
    for(int i = amountVertexes; i > 1; i--){
        cout << fixed << "[" << vertexesIndex[i] << ":" << setw(8) << setprecision(2) << (float)vertexes[vertexesIndex[i]]->d << "]-->";
    }
    cout << "[" << vertexesIndex[1] << ":" << setw(8) << setprecision(2) << (float)vertexes[vertexesIndex[1]]->d << "]." << endl;
}

//prints Length between two points
void Util :: printLength(int source, int destination){
    if((vertexes[destination]->pi == NULL) && vertexes[destination] != vertexes[source]){
        cout << "There is no path from " << source << " to " << destination << "." <<endl;
        return;
    }
    cout << "The length of the shortest path from " << vertexes[source]->vertexName << " to " << vertexes[destination]->vertexName 
         << fixed << " is:" << setw(9) << setprecision(2) << ((float)vertexes[destination]->d) << endl;
}

//prints vertexes used for debugging
void Util :: printVertexes(){
    if(vertexes != NULL){
        for(int i = 1; i <= numVertex; i++){
        cout << "VERTEX: " << vertexes[i]->vertexName << " Value: " << vertexes[i]->d << endl;;
        if(vertexes[i]->pi != NULL){
            cout << "Pi: " << vertexes[i]->pi->vertexName << endl;
        }
        cout << endl;
        cout << endl;
        }
    }
}

//prints the minheap of the vertexes used for debugging
void Util :: printVertexesHeap(){
    if(vertexHeap != NULL){
        for(int i = 1; i <= numVertex; i++){
        cout << "VERTEX: " << vertexHeap[i]->vertexName << " Value: " 
             << setprecision(2) << std::fixed << vertexHeap[i]->d 
             << " INDEX: " << vertexHeap[i]->index << endl;
            if(vertexes[i]->pi != NULL){
                cout << "Pi: " << vertexes[i]->pi->vertexName << endl;
            }
        }
    }
}
