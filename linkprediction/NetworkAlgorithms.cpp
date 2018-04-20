#include <iostream>
#include <utility>
#include "UndirectedUnweightedGraph.h"

using namespace std;

template <class T>
vector<pair <T, T>> nodePairsWithDistance(UndirectedUnweightedGraph<T> graph, int distance){
    vector<pair <T, T>> lengthDPairs;
    map<T, vector<T>> adjList = graph.getAdjList();
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
        T vertex = it->first;
        vector<T> neighbors = it->second;
        map<T, int> paths = graph.shortestPaths(vertex);

        for (auto path_it = paths.begin(); path_it != paths.end(); ++path_it){
            T node = path_it->first;
            int length = path_it->second;
            if (length == distance){
                lengthDPairs.push_back(make_pair(vertex, node));
            }
        }
    }
    return lengthDPairs;
}
