#ifndef UndirectedUnweightedGraph_h
#define UndirectedUnweightedGraph_h


#include <string>
#include <vector>
#include <map>

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
    adjList[node] = vector<T>();
}

template <class T>
void UndirectedUnweightedGraph<T>::addEdge(T node1, T node2){
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
