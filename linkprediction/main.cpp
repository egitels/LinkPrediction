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
   // for(int i =0; i<gcc.V;i++){
//	for(int j=i+1;j<gcc.V;j++){
//		scores.push_back(gcc.Djikstras(i,j));
//	}
  //  }
    scores.push_back(gcc.Djikstras(0,6));
    scores.push_back(gcc.Djikstras(0,4));
    for(int i = 0;i<scores.size();i++){
	cout<<scores[i]<<endl;
    }
    


    return 0;
}
