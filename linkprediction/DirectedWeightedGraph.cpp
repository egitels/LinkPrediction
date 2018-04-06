#include "DirectedWeightedGraph.h"

DirectedWeightedGraph::DirectedWeightedGraph(int V){
    this->V = V;
    for(int i = 0; i<V+1;i++){
        adjVector.push_back(*newNode(i,NULL));
    }
    
}
void DirectedWeightedGraph::addEdge(int src, int dest, int destWeight){
    adjVector[src].next = newNode(dest,destWeight);
}
