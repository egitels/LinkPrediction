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
  
    /**Call BFS a bunch of times to find all of the connected components,
     * and then return the largest connected components*/
    DirectedWeightedGraph GCC() const;
    int Djikstras(int src, int dest);
    int LayerDeterminant(vector<int> parent,int vertex, int dest);
    vector<int> BFS(int src) const;

    void print() const;    
};

#endif
