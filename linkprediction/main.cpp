#include "DirectedWeightedGraph.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>

using namespace std;
struct pairs{
    int x;
    int y;
    int pathlength;
    struct pairs* next;
};
struct pairs* newPairs(int xnode, int ynode, int pathlengths){
    struct pairs* newPairs = (struct pairs*)malloc(sizeof(struct pairs*));
    newPairs->x = xnode;
    newPairs->y = ynode;
    newPairs->pathlength = pathlengths;
    return newPairs;
};

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
    vector<pairs> predictions;


    gcc.print();
    cout<<endl; 
    for(int i =0; i<gcc.V;i++){
        for(int j=i+1;j<gcc.V;j++){
            pairs* individual = newPairs(i,j,gcc.Djikstras(i,j)*-1);
            predictions.push_back(*individual);
        }
    }
    
    for(int i =0; i<gcc.V;i++){
        for(int j=i+1;j<gcc.V;j++){
            cout<<predictions[i].pathlength<<" : ";
        }
    }
            
    
    
    return 0;
}
