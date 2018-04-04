//
//  main.cpp
//  LinkPrediction
//
//  Created by Eli Gitelman on 4/1/18.
//  Copyright © 2018 Eli Gitelman. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <iomanip>
#include <string>
#include <random>
#include <time.h>
#include <stack>
using namespace std;

struct node{ //node struct  -> this is a vertex in the graph
    int weight;
    int data;
    struct node* next;
};
struct listHead{
    struct node *head;
};
struct node* newNode(int data, int weight){
    struct node* newNode = (struct node*)malloc(sizeof(struct node*));
    newNode->data = data;
    newNode->next = NULL;
    newNode->weight = weight;
    return newNode;
};

class Graph {// graph is an adjlist representation. we want a vector of linkedlists.
public:
    node *current = NULL;
    int V;
    Graph(int V);
    void addEdge(int src, int dest, int destWeight);
    vector<node> adjVector;
    
};
Graph::Graph(int V){
    this->V = V;
    for(int i = 0; i<V+1;i++){
        adjVector.push_back(*newNode(i,NULL));
    }
    
}
void Graph::addEdge(int src, int dest, int destWeight){
    adjVector[src].next = newNode(dest,destWeight);
}





int main() {
    int v = 65;
    Graph graph(v);
    
    return 0;
}

