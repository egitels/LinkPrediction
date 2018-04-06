#ifndef DirectedWeightedGraph_h
#define DirectedWeightedGraph_h

#include <vector>
#include <stdlib.h> //NULL
#include <string>
#include <sstream>
#include <iostream>
#include "LinkedList.h"
using namespace std;


class DirectedWeightedGraph {// graph is an adjlist representation. we want a vector of linkedlists.
public:
    int V;
    DirectedWeightedGraph(int V);
    void addEdge(int src, int dest, int destWeight);
    string to_string();
    vector<LinkedList> adjVector;    
    void print() const;    
};

#endif
