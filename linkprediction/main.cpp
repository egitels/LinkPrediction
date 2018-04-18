#include "UndirectedUnweightedGraph.h"
#include "NetworkAlgorithms.cpp"
#include <iostream>
int main(){
    UndirectedUnweightedGraph<string> graph;
    
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("B", "D");
    graph.addEdge("C", "E");
    graph.addEdge("C", "F");
    graph.addEdge("B", "F");
    graph.addEdge("D", "G");
   
    vector<pair<string, string> > pairs = graphDistanceScores<string>(graph);
    for (pair<string, string> pair : pairs){
        //cout << pair.first << " " << pair.second << endl;
    }
    
    vector<string> common = graph.commonNeighbors("F", "A");
    for (string node : common){
        cout << node << " ";
    }
    cout << endl;

    //std::cout << std::endl;
    //std::cout << graph.toString() << std::endl;
    
    return 0;
}
