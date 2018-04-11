#include "DirectedWeightedGraph.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int v = 10;
    DirectedWeightedGraph graph(v);
    
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(5, 4, 1);
    graph.addEdge(4, 6, 1);
    graph.addEdge(6, 7, 1);
//    graph.print();
  
        
    DirectedWeightedGraph gcc = graph.GCC();
    gcc.print();
    cout<<endl; 
    vector<int> scores;    
    for(int i =0; i<gcc.V;i++){
        for(int j=i+1;j<gcc.V;j++){
            scores.push_back(gcc.Djikstras(i,j));
        }
    }
    for(int i = 0;i<scores.size();i++){
        scores[i] = scores[i]*-1
    } //here we take the negative of every score, we need to find a good method of knowing what 2 nodes we took the shortest path from to get the weight at each index, because we have to sort this vector


    return 0;
}
