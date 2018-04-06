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

std::string DirectedWeightedGraph::to_string(){
    string out = "";
    for (size_t i = 0; i < adjVector.size(); ++i){
        out += std::to_string(i) + ": ";
        LinkedList::node *current = adjVector[i].getHead();
        while (current != NULL){
            out += "->" + std::to_string(current->data) + "(" + std::to_string(current->weight) + ") ";
            current = current->next;
        }
        out += "\n";
    }
    return out;
}
