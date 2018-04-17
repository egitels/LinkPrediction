#include "UndirectedUnweightedGraph.h"
#include <iostream>
int main(){
    UndirectedUnweightedGraph<string> graph;
    graph.addNode("Adam");
    graph.addNode("Eli");
    graph.addNode("Dan");
    graph.addNode("John");
    graph.addNode("Carrie");

    graph.addEdge("Adam", "Eli");
    graph.addEdge("Eli", "Dan");
    graph.addEdge("Eli", "Carrie");
    graph.addEdge("Dan", "John");

    std::cout << graph.toString() << std::endl;
    std::cout<< graph.getSize() << std::endl;
    return 0;
}
