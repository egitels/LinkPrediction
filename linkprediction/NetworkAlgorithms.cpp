#include <iostream>
#include <utility>
#include "UndirectedUnweightedGraph.h"

using namespace std;

template <class T>
vector<pair <T, T>> graphDistanceScores(UndirectedUnweightedGraph<T> graph){
    vector<pair <T, T>> length2Pairs;
    map<T, vector<T>> adjList = graph.getAdjList();
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
        T vertex = it->first;
        vector<T> neighbors = it->second;
        map<T, int> paths = graph.shortestPath(vertex);

        for (auto path_it = paths.begin(); path_it != paths.end(); ++path_it){
            T node = path_it->first;
            int length = path_it->second;
            if (length == 2){
                length2Pairs.push_back(make_pair(vertex, node));
            }
        }
    }
    return length2Pairs;
}
