#include "DirectedWeightedGraph.h"
#include "LinkedList.h"
#include <list>

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
    
//    for (int i : maxComponent){
//        if (i > biggestNode){
//            biggestNode = i;
//        }
//    } // switched this into the loop above because if you ran BFS on 0 and it was the original node (with current graph in main) you'd get 4 as your biggest node not 0.
    DirectedWeightedGraph subGraph(V+1); //this was biggestnode+1 which for the current graph is 0+1 so needs to be max component vector size
    
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


/*vector<int> DirectedWeightedGraph::GCC() const{
    vector<bool> visited(V, false);
    vector< vector<int>> components; 
    
    int nextNode = 0;
    bool allFound = false;

    while (!allFound){

        vector<bool> nextVisited = BFS(nextNode);
        vector<int> nextComponent;
        for (size_t index = 0; index < visited.size(); ++index){
            if (nextVisited[index]){
                visited[index] = true;
                nextComponent.push_back(index);
            }
        }
        components.push_back(nextComponent);
 
        nextNode = -1;
        for (int i = 0; i < V; ++i){
            if (!visited[i]){
                nextNode = i;
                break;
            }
        }
        
        if (nextNode == -1){
            allFound = true;
        }
    }
    
    int best_index = -1;
    size_t max_size = 0;
    for (size_t i = 0; i < components.size(); ++i){
        if (components[i].size() > max_size){
            max_size = components[i].size();
            best_index = i;
        }
    }
    return components[best_index];
 
}*/

//breadth-first search on the graph.
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
    vector<bool> discovered(adjVector.size(),false);
    vector<int> parent(adjVector.size(),-1);
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
int DirectedWeightedGraph::LayerDeterminant(vector<int> parent,int vertex, int dest){
    int layer = 0;
    if(parent[vertex] == -1){
        return layer;
    }
    LayerDeterminant(parent,parent[vertex],dest);
    layer++;

    return layer;
}

//print function
void DirectedWeightedGraph::print() const{
    for (size_t i = 0; i < adjVector.size(); ++i){
        cout << i << ": " << adjVector[i] << endl;
    }
}


