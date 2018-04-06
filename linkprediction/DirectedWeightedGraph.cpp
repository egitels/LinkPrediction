#include "DirectedWeightedGraph.h"
#include "LinkedList.h"
DirectedWeightedGraph::DirectedWeightedGraph(int V){
    this->V = V;
    for(int i = 0; i<V;i++){ 
        adjVector.push_back(LinkedList());
    }
    
}
void DirectedWeightedGraph::addEdge(int src, int dest, int destWeight){
    if (src < 0 || src >= (int)adjVector.size()){
        throw std::out_of_range("addEdge: " + std::to_string(src) + " is out of bounds");
    }
    if (dest < 0 || dest >= (int)adjVector.size()){
        throw std::out_of_range("addEdge: " + std::to_string(dest) + " is out of bounds");
    }
    if (destWeight < 0){
        std::logic_error("addEdge: " + std::to_string(destWeight) + " is negative, enter a positive weight");
    }
     
    adjVector[src].add(dest, destWeight);
}

void DirectedWeightedGraph::print() const{
    for (size_t i = 0; i < adjVector.size(); ++i){
        cout << i << ": " << adjVector[i] << endl;
    }
}

