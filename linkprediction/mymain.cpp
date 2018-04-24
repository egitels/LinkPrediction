#include "UndirectedUnweightedGraph.h"
#include "NetworkAlgorithms.cpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>

//Conrad Sanderson and Ryan Curtin.
//Armadillo: a template-based C++ library for linear algebra.
// Journal of Open Source Software, Vol. 1, pp. 26, 2016. 
//

#include <armadillo>
using namespace std;



arma::mat adjacency_matrix(UndirectedUnweightedGraph<string> G){
    map<string, vector<string>> adjlist = G.getAdjList();
    map<string, int> name2idx;

    int N = G.getSize();
    
    arma::mat A(N, N);
    A.fill(0);

    int i = 0; 
    int j = 0;
    
    // create map from strings to indices
    int k = 0;
    for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
        name2idx[it->first] = k;
        k += 1;
    }
    
    for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
        // out += it->first + ": ";        
        vector<string> neighbors = it->second;
        for (string n : neighbors){
            j = name2idx[n]; 
            A(i, j) = 1; 
            j++;
        }

        i++;
        
    }

    return A;
}


map<string, double> katz_ctrlty(UndirectedUnweightedGraph<string> G, double alpha, double beta, double epsilon){    

    arma::mat A = adjacency_matrix(G);
    map<string, vector<string>> adjlist = G.getAdjList();

    map<string, int> name2idx;

    // create map from strings to indices
    int k = 0;
    for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
        name2idx[it->first] = k;
        k += 1;
    }

    if (alpha == -1){

        int D = 0;
        // build the optimal alpha
        
        for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
            vector<string> neighbs = it->second;

            if (neighbs.size() > D){
                D = neighbs.size();
            }
        }

        alpha = 1.0 / (D + 1); 
    }

    arma::mat ones(G.getSize(), 1);
    ones.fill(1);

    arma::mat S0 = A * ones * alpha  + beta; 

    arma::mat Sk = S0;
    
    double delta = 1000000.0;
    
    while (delta > epsilon){
        arma::mat Skp1 = alpha * A * Sk + S0;

        delta = Skp1.max() - Sk.max();
        Sk = Skp1; 
    }
    
    map<string, double> katz_ctrltys;


    for (auto it = adjlist.begin(); it != adjlist.end(); ++it){
        //name2idx[it->first] = k;
        //k += 1;
        int idx = name2idx[it->first];
        
        double ctrlty = arma::as_scalar(Sk[idx]);
        
        katz_ctrltys[it->first] = ctrlty;
    }

    return katz_ctrltys;
}


int main(){
    UndirectedUnweightedGraph<string> graph;
    
    graph.addEdge("A", "B"); 
    graph.addEdge("A", "D");
    graph.addEdge("B", "D");
    graph.addEdge("C", "D");
    graph.addEdge("C", "E");
    graph.addEdge("C", "F");
    graph.addEdge("B", "C");
    graph.addEdge("B", "F");
    graph.addEdge("D", "G");
    
    graph.addEdge("H", "I");
    graph.addEdge("J", "K");
    graph.addEdge("J", "H");
    graph.addEdge("Z", "Y");

    map<string, double> k = katz_ctrlty(graph, -1, 0.05, 0.0000001);

    string out = "";
    for (auto it = k.begin(); it != k.end(); ++it){
        cout << it->first + ":" + to_string(it->second) + ", " << endl;
        cout << endl;
    }
} 
