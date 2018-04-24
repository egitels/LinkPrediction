#include <iostream>
#include <utility>
#include "UndirectedUnweightedGraph.h"
#include <armadillo>
#include <random>
#include <ctime>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

template <class T>
class NetworkAlgorithms{
    public:
        
        NetworkAlgorithms(UndirectedUnweightedGraph<T> graph){
            this->graph = graph;
            length2Pairs = getNodePairsWithDistance(2);

            map<T, vector<T>> adjList = graph.getAdjList();
            
            int k = 0;
            for (auto it = adjList.begin(); it != adjList.end(); ++it){
                name2idxEncoding[it->first] = k;
                idx2nameDecoding[k] = it->first;
                k += 1;
            }
        }
        
        int encodeAsInt(T vertex);
        T decodeFromInt(int index);
        
        vector<pair<T, T>> randomlyGuessEdges(int num);

        vector<pair<T, T>> getNodePairsWithDistance(int distance);
        
        vector<pair<T, T>> findJaccardEfficient();

        pair<T, T> findLargestJaccard(); 
        
        arma::mat katz_scores(double beta, int iterations);
        
        vector<pair<T, T>> getBestKatzPairs(int num, double beta, int iter);
        
        map<T, double> katz_ctrlty(double alpha, double beta, double epsilon);    
         
        vector<pair<T, T>> getBestAdamicPairs(int num);
        
        vector<pair<T, T>> getBestJaccardPairs(int num);

        private:
            UndirectedUnweightedGraph<T> graph; 
            vector<pair<T, T> >length2Pairs;
            arma::mat adjacency_matrix();
            map<T, int> name2idxEncoding;
            map<int, T> idx2nameDecoding;
            
            vector<pair<T, T>> sortAndExtractFrom(map<pair<T, T>, double> m, int num);
};

template <class T>
int NetworkAlgorithms<T>::encodeAsInt(T vertex){
    return name2idxEncoding[vertex]; 
}

template <class T>
T NetworkAlgorithms<T>::decodeFromInt(int index){
    return idx2nameDecoding[index]; 
}

template <class T>
vector<pair <T, T>> NetworkAlgorithms<T>::randomlyGuessEdges(int num){
    vector<pair <T, T>> edgePairs;
    UndirectedUnweightedGraph<T> newEdges;
    srand(time(NULL)); 
    while (edgePairs.size() < num){
        int guess1 = rand() % graph.getSize(); 
        int guess2 = rand() % graph.getSize();
        
        if (guess1 != guess2){
            T node1 = idx2nameDecoding[guess1];
            T node2 = idx2nameDecoding[guess2];
            if (!graph.edgeExists(node1, node2) && !newEdges.edgeExists(node1, node2)){
                edgePairs.push_back(make_pair(node1, node2));
                newEdges.addEdge(node1, node2);
            }
        }
    }  
    return edgePairs;
}


template <class T>
vector<pair <T, T>> NetworkAlgorithms<T>::getNodePairsWithDistance(int distance){
    vector<pair <T, T>> lengthDPairs;
    UndirectedUnweightedGraph<T> chosenPairs;
    map<T, vector<T>> adjList = graph.getAdjList();
    for (auto it = adjList.begin(); it != adjList.end(); ++it){
        T vertex = it->first;
        vector<T> neighbors = it->second;
        map<T, int> paths = graph.shortestPaths(vertex);
        cout << vertex << endl; 
        for (auto path_it = paths.begin(); path_it != paths.end(); ++path_it){
            T node = path_it->first;
            int length = path_it->second;
            if (length == distance && !chosenPairs.edgeExists(vertex, node)){
                lengthDPairs.push_back(make_pair(vertex, node));
                chosenPairs.addEdge(vertex, node);
            }
        }
    }
    return lengthDPairs;
}

template <class T>
vector<pair<T, T> > NetworkAlgorithms<T>::findJaccardEfficient(){
    vector<pair <T, T>> bigOlJaccardPairs;
    map<T, vector<T>> adjList = graph.getAdjList();
    double biggestJaccard = 0;
    for (pair<T, T> p : length2Pairs){
        T node1 = p.first;
        T node2 = p.second;
        
        double calculatedJaccard = graph.Jaccard(node1, node2);
        //if we find a new largest Jaccard, clear the vector and update biggestJaccard
        if (calculatedJaccard > biggestJaccard){
            biggestJaccard = calculatedJaccard;
            bigOlJaccardPairs.clear();
            bigOlJaccardPairs.push_back(make_pair(node1, node2));
        } else if (calculatedJaccard == biggestJaccard){
            bigOlJaccardPairs.push_back(make_pair(node1, node2));
            cout << biggestJaccard << endl;
        }
    }
    return bigOlJaccardPairs;
}


template <class T>
pair<T, T> NetworkAlgorithms<T>::findLargestJaccard(){ 
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

template <class T>
arma::mat NetworkAlgorithms<T>::katz_scores(double beta, int iterations){ 
    arma::mat A = adjacency_matrix();
    map<T, vector<T>> adjlist = graph.getAdjList();
    
    if (beta == -1){

        int D = 0;
        // build the optimal alpha
        
        for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
            vector<T> neighbs = it->second;

            if (neighbs.size() > D){
                D = neighbs.size();
            }
        }

        beta = 1.0 / (D + 1); 
    }

    int N = graph.getAdjList().size(); 
    arma::mat scores(N, N);
    scores.fill(0);
    
    
    arma::mat A_init = A;
    double oldBeta = beta; 
    scores += beta * A;
    
    for (int i = 2; i < iterations; ++i){
        cout << "matrix multiplication #" << i << endl;
        beta*=oldBeta;
        A *= A_init;
        scores += beta * A;
    }
    
    //filter out scores that refer to a path of length 1 or to the same node
    for (int i = 0; i < A_init.n_rows; ++i){
        for (int j = 0; j < A_init.n_cols; ++j){
            int val = A_init(i, j);
            if (val != 0 || i == j){
                scores(i, j) = 0;
            }
        }
    }
    return scores;
}

template <class T>
vector<pair<T, T>> NetworkAlgorithms<T>::getBestKatzPairs(int num, double beta, int iter){
    
    UndirectedUnweightedGraph<T> chosenEdges;
    vector<pair<T, T>> pairs;
    arma::mat scores = katz_scores(beta, iter);
    
    string v1, v2;
    double max_score = -1;
    
    cout << "Getting best " << num << " edges..." << endl;
    while (pairs.size() < num){
    
        arma::uword i = scores.index_max();
        max_score = scores(i);
        int x = i % scores.n_rows;
        int y = i / scores.n_rows;

        v1 = decodeFromInt(x);
        v2 = decodeFromInt(y);
        scores(x, y) = 0;
        if (v1 != v2 && !graph.edgeExists(v1, v2) && !chosenEdges.edgeExists(v1, v2)){
            chosenEdges.addEdge(v1, v2);
            pairs.push_back(make_pair(v1, v2));
        }
    }
    return pairs;
}

template <class T>
map<T, double> NetworkAlgorithms<T>::katz_ctrlty(double alpha, double beta, double epsilon){    
    arma::mat A = adjacency_matrix();
    map<T, vector<T>> adjlist = graph.getAdjList();

    if (alpha == -1){

        int D = 0;
        // build the optimal alpha
        
        for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
            vector<T> neighbs = it->second;

            if (neighbs.size() > D){
                D = neighbs.size();
            }
        }

        alpha = 1.0 / (D + 1); 
    }

    arma::mat ones(graph.getSize(), 1);
    ones.fill(1);

    arma::mat S0 = A * ones * alpha  + beta; 

    arma::mat Sk = S0;
    
    double delta = 1000000.0;
    while (delta > epsilon){
        arma::mat Skp1 = alpha * A * Sk + S0 + beta;

        delta = Skp1.max() - Sk.max();
        Sk = Skp1;
    }
    map<T, double> katz_ctrltys;


    for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
        //name2idx[it->first] = k;
        //k += 1;
        int idx = name2idxEncoding[it->first];
        
        double ctrlty = arma::as_scalar(Sk[idx]);
        
        katz_ctrltys[it->first] = ctrlty;
    }

    return katz_ctrltys;
}

template <class T>
vector<pair<T, T>> NetworkAlgorithms<T>::getBestAdamicPairs(int num){
    map<pair<T, T>, double> scores;
    for (pair<T, T> p : length2Pairs){
        scores[p] = graph.adamicAdar(p.first, p.second);
    }

    return sortAndExtractFrom(scores, num);
}

template <class T>
vector<pair<T, T>> NetworkAlgorithms<T>::getBestJaccardPairs(int num){
    map<pair<T, T>, double> scores;
    for (pair<T, T> p : length2Pairs){
        scores[p] = graph.Jaccard(p.first, p.second);
    }

    return sortAndExtractFrom(scores, num);
}

template <class T>
arma::mat NetworkAlgorithms<T>::adjacency_matrix(){
    map<T, vector<T>> adjlist = graph.getAdjList();

    int N = graph.getSize();
    
    arma::mat A(N, N);
    A.fill(0);

    int i = 0; 
    int j = 0;
    
    for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
        i = name2idxEncoding[it->first];
        vector<T> neighbors = it->second;
        for (T n : neighbors){
            j = name2idxEncoding[n]; 
            A(i, j) = 1; 
        }
    }
    return A;
}

template <class T>
vector<pair<T, T>> NetworkAlgorithms<T>::sortAndExtractFrom(map<pair<T, T>, double> m, int num){

    typedef std::function<bool(pair<pair<T,T>, double>, pair<pair<T,T>, double>)> Comparator;
    // Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
			[](pair<pair<T,T>, double> elem1 ,pair<pair<T,T>, double> elem2)
			{
				return elem1.second > elem2.second;
			};
    std::set<pair<pair<T,T>, double>, Comparator> sortedSet(
			m.begin(), m.end(), compFunctor);

    vector<pair<T, T>> bestPairs;
    for (pair<pair<T,T>, double> p : sortedSet){
        bestPairs.push_back(p.first);
        if (bestPairs.size() == num){
            break;
        }
    }
    return bestPairs;
}
