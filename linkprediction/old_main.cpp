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
struct CNeighbors{
    int x;
    int y;
    int numNeigh;
    struct CNeighbors* next;
};
struct CNeighbors* newCNeighbors(int xnode, int ynode, int numNeighs){
    struct CNeighbors* newCNeighbors;
    newCNeighbors->x = xnode;
    newCNeighbors->y = ynode;
    newCNeighbors->numNeigh = numNeighs;
    return newCNeighbors;
}

int main() {
    int v = 7;
    DirectedWeightedGraph graph(v);
    
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 6, 1);
    graph.addEdge(6, 5, 1);
    graph.addEdge(5, 3, 1);
//    graph.print();
  
     
    DirectedWeightedGraph gcc = graph.GCC();


    gcc.print();
    cout<<endl;
//random method start
    
    int num1 = gcc.random();
    int num2 = gcc.random();
    while(num1 == num2){
        num1 = gcc.random();
    }
    cout<<"random link from node: "<<num1<<"->"<<num2<<endl;
//random method end
//graph distance method start
    vector<pairs> gdPredictions;
    for(int i =0; i<gcc.V;i++){
        for(int j=i+1;j<gcc.V;j++){
            pairs* individual = newPairs(i,j,gcc.Djikstras(i,j)*-1);
            gdPredictions.push_back(*individual);
        }
    }

    for(int i =0; i<sizeof(gdPredictions);i++){
        cout<<"for path "<<gdPredictions[i].x<<"->"<<gdPredictions[i].y<<" the shortest path is length: "<<gdPredictions[i].pathlength<<endl;
    }
//graph distance method end
//common neighbors method begin
    vector<CNeighbors> cnPredictions;
    for(int i = 0; i<gcc.V;i++){
        for(int j =i+1;j<gcc.V;j++){
            CNeighbors* neigh = newCNeighbors(i,j,gcc.CommonNeighbors(i,j));
            cnPredictions.push_back(*neigh);
        }
    }
    for(int i =0; i<sizeof(cnPredictions);i++){
        cout<<"the number of common neighbors between  "<<cnPredictions[i].x<<"->"<<cnPredictions[i].y<<"is: "<<cnPredictions[i].numNeigh<<endl;
    }
//common neighbors method end
    
    
return 0;
}
