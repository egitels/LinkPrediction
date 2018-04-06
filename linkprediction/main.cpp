#include "DirectedWeightedGraph.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

int main() {
    int v = 10;
    DirectedWeightedGraph graph(v);
    
    graph.addEdge(0, 5, 20);
    graph.addEdge(0, 4, 1);
    graph.addEdge(0, 3, 2);
    graph.addEdge(8, 9, 3);
    graph.addEdge(8, 5, 17);
    graph.addEdge(8, 2, 3);
   
    graph.print();
    
    return 0;
}
