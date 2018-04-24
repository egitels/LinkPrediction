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

template <class T>
pair<T, T> findLargestJaccard(UndirectedUnweightedGraph<T> graph){ 
    pair <T, T> bigOlJaccardPair;
    map<T, vector<T>> adjList = graph.getAdjList();
    double biggestJaccard = 0;
    for (auto it1 = adjList.begin(); it1 != adjList.end(); ++it1){
        T vertex1 = it1->first;
        for (auto it2 = adjList.begin(); it2 != adjList.end(); ++it2){
            T vertex2 = it2->first;
            if (vertex1 != vertex2 && !graph.edgeExists(vertex1, vertex2)){
                double calculatedJaccard = graph.Jaccard(vertex1, vertex2);
                if (calculatedJaccard > biggestJaccard){
                    biggestJaccard = calculatedJaccard;
                    bigOlJaccardPair = make_pair(vertex1, vertex2);
                    cout << biggestJaccard << endl;
                }
                else if (calculatedJaccard == biggestJaccard){
                    cout << vertex1 << calculatedJaccard << endl;
                }
            }   
        }
    }
    return bigOlJaccardPair;
}
