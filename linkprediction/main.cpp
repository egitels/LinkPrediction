#include "UndirectedUnweightedGraph.h"
#include "NetworkAlgorithms.cpp"
#include <iostream>
int main(){
    UndirectedUnweightedGraph<string> graph;
    
    graph.addEdge("A", "B"); 
    graph.addEdge("A", "D");
    graph.addEdge("B", "D");
    graph.addEdge("C", "D");
    graph.addEdge("C", "E");
    graph.addEdge("C", "F");
    graph.addEdge("B", "C");
    graph.addEdge("B", "F");
    graph.addEdge("D", "G");
    
    graph.addEdge("H", "I");
    graph.addEdge("J", "K");
    graph.addEdge("J", "H");
    graph.addEdge("Z", "Y");
    
    cout << "Original graph:" << endl;
    cout << graph.toString() << endl;
    cout << "GCC of graph:" << endl;
    cout << graph.GCC().toString() << endl;
    
    cout << "Pairs of nodes of distance 2:" << endl;
    vector<pair<string, string> > pairs = nodePairsWithDistance<string>(graph, 2);
    for (pair<string, string> pair : pairs){
        cout << "{" << pair.first << " " << pair.second << "}" << " ";
    }
    cout << endl;
    
    cout << "\nCommon neighbors between C and A:" << endl;
    vector<string> common = graph.commonNeighbors("C", "A");
    for (string node : common){
        cout << node << " ";
    }
    cout << endl;
    

    
    return 0;
}
