#include "UndirectedUnweightedGraph.h"

UndirectedUnweightedGraph::UndirectedUnweightedGraph(){}

void UndirectedUnweightedGraph::addNode(string node){
    adjList[node] = vector<string>();
}

void UndirectedUnweightedGraph::addEdge(string node1, string node2){
    adjList[node1].push_back(node2);
    adjList[node2].push_back(node1);
}

bool UndirectedUnweightedGraph::edgeExists(string node1, string node2){
    for (string node : adjList[node1]){
        if (node == node2){
            return true;
        }
    }
    return false;
}

int UndirectedUnweightedGraph::getSize() const{
    return adjList.size();
}

string UndirectedUnweightedGraph::toString(){
    string out = "";
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
       out += it->first + ": ";
       for (string n : it->second){
           out += n + " ";
       }
       out += "\n";
    }
    return out;
}
