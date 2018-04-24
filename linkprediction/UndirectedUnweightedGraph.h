#ifndef UndirectedUnweightedGraph_h
#define UndirectedUnweightedGraph_h


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <math.h>
using namespace std;

/**
 * Undirected Graph data structure, implemented using a map of vectors.
 * This class is generic, and will support nodes of any data type.
 */
template <class T>
class UndirectedUnweightedGraph {
    public:

        /**
         * Add a node to the graph.
         * Initializes empty vector for the node key in the adjacency list.
         * @param node The node to add to the graph.
         */
        void addNode(T node);

        /**
         * Add an edge to the graph, between two nodes.
         * @param node1 First node to add an edge to
         * @param node2 Second node to add an edge to
         */
        void addEdge(T node1, T node2);
        
        /**
         * Check to see if an edge exists between two nodes.
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
        
        double percentPairsCorrect(vector<pair<T, T>> pair);

        /**
         * Return the adjacency list data structure that represents this graph.
         */
        map<T, vector<T>> getAdjList() const;
        
        /**
         * Return the greatest connected component of the graph.
         */
        UndirectedUnweightedGraph<T> GCC();

        /**
         * Return all of the connected components in the graph.
         */
        vector<vector<T> > getAllComponents();

        /**
         * Run a breadth-first search on tue graph, starting at some source node.
         * @param src The source node
         * return all nodes found from the search as vector
         */
        vector<T> BFS(T src);
        
        /**
         * Get the shortest paths between some source node and every other
         * node it is connected to.
         * @param src The source node
         * return the shortest paths represented as a map, with the value of each
         *  (key, value) pair of the map representing the distance between that node key
         *  and the source node.
         */
        map<T, int> shortestPaths(T src);

        /**
         * Get the common neighbors that node1 and node2 share.
         * Invariant: the nodes should be seperated by a path length of exactly 2,
         * otherwise calling this method does not make sense.
         * @param node1 The first node
         * @param node2 The second node
         * return a vector containing the intersection of neighbors between node1 and node2
         */
        vector<T> commonNeighbors(T node1, T node2);

        /**
         * Return a string representation of the graph.
         */
        std::string toString();
        
        /**
        *
        *returns the score of the intersection of the neighbors of node1 and node2 divded by the union of the neghbors of node1
        * and node 2.
        */
        double Jaccard(T node1, T node2);

        /*
        *The jaccard * 1/the frequency of similar nodes
        */

        double adamicAdar(T node1, T node2);
        
        /*
        *The product of the number of neighbors of x and y
        */
        int preferentialAttachment(T node1, T node2);
       /*
        *The sum of the ensemble of all paths from x to y
        */
        int Katz(T node1, T node2);
        /* we reduce the size of the graph by 1-p where p is the number of pairs with the lowest score found from katz, then we
        * rerun katz to find scores
        */
        int katzClustering(T node1, T node2);
        /*returns score based on the intersection of the neighbors of nodes similar to x and the neighbors of y
        */
        int Bigram(T node1, T node2);
    private:
        map<T, vector<T> > adjList;
        
        /*
         * Given a vector of nodes that are a subset of the original graph,
         * create a subgraph containing only those nodes.
         * @param nodes The vector containing subset of nodes of original graph
         * return A subgraph consisting of only those nodes passed in
         */
        UndirectedUnweightedGraph<T> reconstructSubGraph(vector<T> nodes);

};

template <class T>
void UndirectedUnweightedGraph<T>::addNode(T node){ 
    if (adjList.count(node)){
        throw std::logic_error("Node \"" + node + "\" already exists");
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

    if (edgeExists(node1, node2)){
        throw std::logic_error("Edge already exists between nodes \"" + 
                node1 + "\" and \"" + node2 + "\"");
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
double UndirectedUnweightedGraph<T>::percentPairsCorrect(vector<pair<T, T>> pairs){
    double correct = 0;
    for (pair<string, string> p : pairs){
        if (edgeExists(p.first, p.second)){
            correct++;
        }
    }
    return correct/pairs.size();
}

template <class T>
map<T, vector<T> > UndirectedUnweightedGraph<T>::getAdjList() const{
    return adjList;
}

template <class T>
UndirectedUnweightedGraph<T> UndirectedUnweightedGraph<T>::GCC() {
    vector<vector<T> > allComponents = getAllComponents(); 
    vector<T> maxComponent;
    for (vector<T> component: allComponents){
        if (component.size() > maxComponent.size()){
            maxComponent = component;
        }
    }
    return reconstructSubGraph(maxComponent);
}

template <class T>
vector<vector<T> > UndirectedUnweightedGraph<T>::getAllComponents() {
    map<T, bool> visited;
    
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
        visited[it->first] = false;
    }
    vector<vector<T >> allComponents;
    int foundCount = 0; 
    
    while (foundCount < adjList.size()){
        
        T current;
        for (auto it = visited.begin(); it != visited.end(); ++it){
            if (it->second == false){
                current = it->first;
                break;
            }
        }

        vector<T> found = BFS(current);
        allComponents.push_back(found);
        foundCount += found.size();
        for (T node : found){
            visited[node] = true;
        }
    }
    return allComponents;
}

//done
template <class T>
vector<T> UndirectedUnweightedGraph<T>::BFS(T src) {
    vector<T> found;
    
    map <T, bool> discovered;
    discovered[src] = true;
    found.push_back(src);

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

//done
template <class T>
map<T, int> UndirectedUnweightedGraph<T>::shortestPaths(T src) {
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

template <class T>
vector<T> UndirectedUnweightedGraph<T>::commonNeighbors(T node1, T node2){
    vector<T> n1Neighbors = adjList[node1];
    vector<T> n2Neighbors = adjList[node2];
    sort(n1Neighbors.begin(), n1Neighbors.end());
    sort(n2Neighbors.begin(), n2Neighbors.end());
    vector<T> intersection;
    set_intersection(n1Neighbors.begin(), n1Neighbors.end(), n2Neighbors.begin(),
            n2Neighbors.end(), inserter(intersection, intersection.begin()));
    return intersection;
}

template <class T>
double UndirectedUnweightedGraph<T>::Jaccard(T node1, T node2){
    vector<T> n1Neighbors = adjList[node1];
    vector<T> n2Neighbors = adjList[node2];
    sort(n1Neighbors.begin(), n1Neighbors.end());
    sort(n2Neighbors.begin(), n2Neighbors.end());
    vector<T> neighborUnion;
    set_union(n1Neighbors.begin(), n1Neighbors.end(), n2Neighbors.begin(),
            n2Neighbors.end(), inserter(neighborUnion, neighborUnion.begin()));
    
    double common = commonNeighbors(node1, node2).size();
    double all = neighborUnion.size();

    return common/all;
}

template <class T>
double UndirectedUnweightedGraph<T>::adamicAdar(T node1, T node2){
    vector<T> common = commonNeighbors(node1, node2);
    double score = 0;
    for (T node : common){
        score += 1 / (log(adjList[node].size()));
    }
    return score;
}

template <class T>
int UndirectedUnweightedGraph<T>::preferentialAttachment(T node1, T node2){
    return adjList[node1].size() * adjList[node2].size();
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

template <class T>
UndirectedUnweightedGraph<T> UndirectedUnweightedGraph<T>::reconstructSubGraph(vector<T> nodes){
    UndirectedUnweightedGraph<T> gcc;
    for (T node : nodes){
        for (T neighbor : adjList[node]){
            if (!gcc.edgeExists(node, neighbor)){
                gcc.addEdge(node, neighbor);
            }
        }
    }
    return gcc;
}

#endif
