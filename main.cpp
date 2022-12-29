#include <iostream>
#include <string.h>
#include "Util.h"

using std::cerr;
using std::endl;
using std::cout;

int main(int argc, char** argv){
    if(argc != 3 || (strcmp("Directed", argv[1]) != 0 && strcmp("Undirected", argv[1])))
    {
        cerr << "Usage: ./PJ3 <GraphType> <InputFile>" << endl;
        return 0;
    }

    Util* run = new Util(argv[1], argv[2]);

    delete run;
}