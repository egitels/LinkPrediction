#ifndef UndirectedUnweightedGraph_h
#define UndirectedUnweightedGraph_h


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>

using namespace std;
/**
 * Undirected Graph data structure, implemented using a map of vectors.
 */
template <class T>
class UndirectedUnweightedGraph {
    public:

        /**
         * Undefined.
         */
        void addNode(T node);

        /**
         * Add an edge to the graph, between two nodes.
         * If either node is out of bounds of the graph, this method will throw an
         * out_of_range exception.
         * @param node1 First node to add an edge to
         * @param node2 Second node to add an edge to
         */
        void addEdge(T node1, T node2);
        
        /**
         * Check to see if an edge exists between two nodes.
         * If either node is out of bounds of the graph, this method will throw an
         * out_of_range exception.
         * @param node1 First node to check if edge exists
         * @param node2 Second node to check if edge exists
         * return true if an edge exists between
         *  the two nodes, false otherwise.
         */
        bool edgeExists(T node1, T node2);
        
        /**
         * Return the number of nodes contained by the graph.
         */
        int getSize() const;
        
        map<T, vector<T>> getAdjList() const;

        vector<T> BFS(T src);
        
        map<T, int> shortestPath(T src);

        vector<T> commonNeighbors(T node1, T node2);

        /**
         * Return a string representation of the graph.
         */
        std::string toString();

        void testComp();
        
    private:
        map<T, vector<T> > adjList;

};

template <class T>
void UndirectedUnweightedGraph<T>::addNode(T node){ 
    if (adjList.count(node)){
        //throw some kind of error
    } 

    adjList[node] = vector<T>();
}

template <class T>
void UndirectedUnweightedGraph<T>::addEdge(T node1, T node2){
    if (!adjList.count(node1)){
        addNode(node1);
    } 
    if (!adjList.count(node2)){
        addNode(node2);
    }

    adjList[node1].push_back(node2);
    adjList[node2].push_back(node1);
}

template <class T>
bool UndirectedUnweightedGraph<T>::edgeExists(T node1, T node2){
    for (T node : adjList[node1]){
        if (node == node2){
            return true;
        }
    }
    return false;
}

template <class T>
int UndirectedUnweightedGraph<T>::getSize() const{
    return adjList.size();
}

template <class T>
map<T, vector<T> > UndirectedUnweightedGraph<T>::getAdjList() const{
    return adjList;
}

template <class T>
vector<T> UndirectedUnweightedGraph<T>::BFS(T src) {
    vector<T> found;
    
    map <T, bool> discovered;
    discovered[src] = true;

    list<T> queue;
    queue.push_back(src);
    while (!queue.empty()){
        T vertex = queue.front();
        queue.pop_front();
        
        for (T current : adjList[vertex]){
            if (!discovered[current]){
                queue.push_back(current);
                discovered[current] = true;
                found.push_back(current);
            }
        }
    }
    return found;
}

template <class T>
map<T, int> UndirectedUnweightedGraph<T>::shortestPath(T src) {
    map <T, bool> discovered;
    map <T, int> dist;
    discovered[src] = true;
    dist[src] = 0;
    list<T> queue;
    queue.push_back(src);
    while (!queue.empty()){
        T vertex = queue.front();
        queue.pop_front();
        
        for (T current : adjList[vertex]){
            if (!discovered[current] && current != src){
                queue.push_back(current);
                discovered[current] = true;
                dist[current] = dist[vertex] + 1;
            }
        }
    }
    return dist;
}

//doesn't appear to work yet...
template <class T>
vector<T> UndirectedUnweightedGraph<T>::commonNeighbors(T node1, T node2){
    vector<T> n1Neighbors = adjList[node1];
    vector<T> n2Neighbors = adjList[node2];
    vector<T> intersection;
    set_intersection(n1Neighbors.begin(), n1Neighbors.end(), n2Neighbors.begin(),
            n2Neighbors.end(), inserter(intersection, intersection.begin()));
    return intersection;
}

template <class T>
string UndirectedUnweightedGraph<T>::toString(){
    T out = "";
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
       out += it->first + ": ";
       for (T n : it->second){
           out += n + " ";
       }
       out += "\n";
    }
    return out;
}

#endif
