#include "DirectedWeightedGraph.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int v = 6;
    DirectedWeightedGraph graph(v);
    
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(5, 4, 1);

//    graph.print();
  
        
    DirectedWeightedGraph gcc = graph.GCC();
    
   
    
    gcc.print();


    return 0;
}
