#ifndef UndirectedUnweightedGraph_h
#define UndirectedUnweightedGraph_h


#include <string>
#include <vector>
#include <map>

using namespace std;
/**
 * Undirected Graph data structure, implemented using a map of vectors.
 */
class UndirectedUnweightedGraph {
    public:
        /**
         * UndirectedUnweightedGraph constructor.
         */
        UndirectedUnweightedGraph();

        /**
         * Undefined.
         */
        void addNode(string node);

        /**
         * Add an edge to the graph, between two nodes.
         * If either node is out of bounds of the graph, this method will throw an
         * out_of_range exception.
         * @param node1 First node to add an edge to
         * @param node2 Second node to add an edge to
         */
        void addEdge(string node1, string node2);
        
        /**
         * Check to see if an edge exists between two nodes.
         * If either node is out of bounds of the graph, this method will throw an
         * out_of_range exception.
         * @param node1 First node to check if edge exists
         * @param node2 Second node to check if edge exists
         * return true if an edge exists between
         *  the two nodes, false otherwise.
         */
        bool edgeExists(string node1, string node2);
        
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
        map<string, vector<string> > adjList;
};

#endif
