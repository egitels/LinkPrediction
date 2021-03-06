#include "DirectedWeightedGraph.h"
#include "LinkedList.h"
#include <list>
#include <time.h>

//creates a Directed graph with number of nodes(vertexes) V, graph is a vector of linkedlists
DirectedWeightedGraph::DirectedWeightedGraph(int V){
    this->V = V;
    for(int i = 0; i<V;i++){ 
        adjVector.push_back(LinkedList());
    }
    
}
// adds an edge with error processing for a weighted directed graph
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
    adjVector[dest].add(src, destWeight);
}
//finds the GCC of a graph, directed or undirected.
DirectedWeightedGraph DirectedWeightedGraph::GCC() const{
    
    int biggestNode = 0;
    vector<int> maxComponent;
    for (int i = 0; i < V; ++i){
        vector<int> found = BFS(i);
        if (found.size() > maxComponent.size()){
            maxComponent = found;
            biggestNode = i;
        }
    }
    
 DirectedWeightedGraph subGraph(V+1);    
    for (int i = 0; i < subGraph.V; ++i){
 
        
        LinkedList::node* current;
        current = adjVector[i].getHead();
        while (current != NULL){
            subGraph.addEdge(i, current->data, current->weight);
            current = current->next;
        }
    }
    return subGraph;

}
vector<int> DirectedWeightedGraph::BFS(int src) const{
    vector<int> found;
    vector<bool> discovered(adjVector.size(), false); 
    discovered[src] = true;
    
    list<int> queue; 
    queue.push_back(src);
    
    while (!queue.empty()){
        int vertex = queue.front();
        queue.pop_front();

        LinkedList::node* current;
        current = adjVector[vertex].getHead();
        while (current != NULL){
            if (!discovered[current->data]){
                discovered[current->data] = true;
                queue.push_back(current->data);
                found.push_back(current->data);
            }
            current = current->next;
        }
    }   
    return found;
}
int DirectedWeightedGraph::Djikstras(int src, int dest){
    bool *discovered = new bool[V*2];
    int *parent = new int[V*2];
    for (int i = 0; i < 2*V; i++)
    {
        discovered[i] = false;
        parent[i] = -1;
    }
    discovered[src] = true;
    
    list<int> queue;
    queue.push_back(src);
    while(!queue.empty()){
        int vertex = queue.front();
        if (vertex == dest){
            return LayerDeterminant(parent, vertex, dest);
        }
        queue.pop_front();
        
        LinkedList::node* current;
        current = adjVector[vertex].getHead();
        while(current != NULL){
            if(!discovered[current->data]){
                discovered[current->data] = true;
                queue.push_back(current->data);
                parent[current->data] = vertex;
            }
            current = current->next;
        }
    }
 return -1; 
}
int DirectedWeightedGraph::LayerDeterminant(int parent[],int vertex, int dest){
    layer = 0;
    if(parent[vertex] == -1){
        return layer;
    }
    LayerDeterminant(parent,parent[vertex],dest);
    layer++;

    return layer;
}

int DirectedWeightedGraph::CommonNeighbors(int src, int dest){
    vector<int> srcNeighbors;
    vector<int> destNeighbors;
    vector<int> neighbors;
    LinkedList::node* srcCurrent;
    LinkedList::node* destCurrent;
    srcCurrent = adjVector[src].getHead();
    while(srcCurrent != NULL){
        srcNeighbors.push_back(srcCurrent->data);
        srcCurrent = srcCurrent->next;
    }
    destCurrent = adjVector[dest].getHead();
    while(destCurrent != NULL){
        destNeighbors.push_back(destCurrent->data);
        destCurrent = destCurrent->next;
    }
    for(int i = 0; i<srcNeighbors.size();i++){
        for(int j = 0; j < destNeighbors.size();j++){
            if(srcNeighbors[i] == destNeighbors[j]){
                neighbors.push_back(srcNeighbors[i]);
            }
        }
    }
    return neighbors.size(); 
    
}
int DirectedWeightedGraph::random(){
    int random;
    srand (time(NULL));
    random = rand()%V+1;
    
    return random;
    
    
}

//print function
void DirectedWeightedGraph::print() const{
    for (size_t i = 0; i < adjVector.size(); ++i){
        cout << i << ": " << adjVector[i] << endl;
    }
}


