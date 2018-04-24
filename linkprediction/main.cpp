#include "UndirectedUnweightedGraph.h"
#include "NetworkAlgorithms.cpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::string> split(std::string const &string_in){
    std::istringstream buffer(string_in);
    std::vector<std::string> ret;
    std::copy(std::istream_iterator<std::string>(buffer),
            std::istream_iterator<std::string>(),
            std::back_inserter(ret));
    
    return ret;
}

void readGraphFromFile(UndirectedUnweightedGraph<string>& graph, string graph_file){
    std::ifstream edgeList;
    edgeList.open(graph_file);

    std::string line;
    if (edgeList.is_open()){
        while ( getline (edgeList, line) ){
            std::vector<std::string> edges;
            edges = split(line);
            
            std::stringstream toNumber(edges[0]);
            string edge1;
            toNumber >> edge1;
            toNumber = std::stringstream(edges[1]);
            string edge2;
            toNumber >> edge2;
            if (!graph.edgeExists(edge1, edge2)){
                graph.addEdge(edge1, edge2);
            }
        }
    } else {
        std::cout << "Unable to open file.";
    }
}

int main(){
    string year1 = "edgelists/as-ph/1994.txt";
    string year2 = "edgelists/as-ph/1995.txt";
    string year3 = "edgelists/as-ph/1996.txt";
    UndirectedUnweightedGraph<string> graph1;
    readGraphFromFile(graph1, year1);
    readGraphFromFile(graph1, year2);
    readGraphFromFile(graph1, year3);
    
    string year4 = "edgelists/as-ph/1997.txt";
    string year5 = "edgelists/as-ph/1998.txt";
    string year6 = "edgelists/as-ph/1999.txt";
    UndirectedUnweightedGraph<string> graph2;
    readGraphFromFile(graph2, year4);
    readGraphFromFile(graph2, year5);
    readGraphFromFile(graph2, year6);
    
    graph1 = graph1.GCC();

    /*
    UndirectedUnweightedGraph<string> graph1; 
    graph1.addEdge("A", "B"); 
    graph1.addEdge("A", "C");
    graph1.addEdge("A", "D");
    graph1.addEdge("A", "E");
    graph1.addEdge("E", "F");
    graph1.addEdge("D", "F");
    graph1.addEdge("C", "F");
    graph1.addEdge("B", "F");
    */


    NetworkAlgorithms<string> algorithms(graph1);
    
    /*
    vector<pair<string, string>> pairs = algorithms.getBestBigrams(2, 3);
    
    for (pair<string, string> p : pairs){
        cout << p.first << " " << p.second << endl;
    }
    */

    int numGuesses = 1000;

    double percentCorrect = 0;
    
    vector<pair<string, string>> bigramPairs1 = algorithms.getBestBigrams(numGuesses, 8);
    percentCorrect = graph2.percentPairsCorrect(bigramPairs1) * 100;
    printf("Percent correct (Bigrams with d=8): %4.3f\n", percentCorrect);

    vector<pair<string, string>> bigramPairs2 = algorithms.getBestBigrams(numGuesses, 16);
    percentCorrect = graph2.percentPairsCorrect(bigramPairs2) * 100;
    printf("Percent correct (Bigrams with d=16): %4.3f\n", percentCorrect);


    /*
    vector<pair<string, string>> preferrentialAttachmentPairs = algorithms.getBestPreferrentialPairs(numGuesses);
    percentCorrect = graph2.percentPairsCorrect(preferrentialAttachmentPairs) * 100;
    printf("Percent correct (Preferrential Attachment): %4.3f\n", percentCorrect);
    */
    
    /*
    vector<pair<string, string>> graphDistancePairs = algorithms.getRandomGraphDistance(numGuesses);
    percentCorrect = graph2.percentPairsCorrect(graphDistancePairs) * 100;
    printf("Percent correct (Graph Distance): %4.3f\n", percentCorrect);
    
    vector<pair<string, string>> commonNeighborPairs = algorithms.getBestCommonNeighborPairs(numGuesses);
    percentCorrect = graph2.percentPairsCorrect(commonNeighborPairs) * 100;
    printf("Percent correct (Common Neighbors): %4.3f\n", percentCorrect);

    vector<pair<string, string>> jaccardPairs = algorithms.getBestJaccardPairs(numGuesses);
    percentCorrect = graph2.percentPairsCorrect(jaccardPairs) * 100;
    printf("Percent correct (Jaccard): %4.3f\n", percentCorrect);
    
    vector<pair<string, string>> adamicPairs = algorithms.getBestAdamicPairs(numGuesses);
    percentCorrect = graph2.percentPairsCorrect(adamicPairs) * 100;
    printf("Percent correct (Adamic): %4.3f\n", percentCorrect);
    */

    //vector<pair<string, string>> katzPairs = algorithms.getBestKatzPairs(numGuesses, 0.0005, 50);
    //percentCorrect = graph2.percentPairsCorrect(katzPairs) * 100;
    //printf("Percent correct: %4.3f\n", percentCorrect);

    //vector<pair<string, string>> randPairs = algorithms.randomlyGuessEdges(numGuesses);
    //percentCorrect = graph2.percentPairsCorrect(randPairs) * 100;
    //printf("Percent correct: %4.3f\n", percentCorrect);
   
    

    
    /*map<string, double> k = algorithms.katz_ctrlty(-1, 0.05, 0.0000000001);
    
    string out = "";
    for (auto it = k.begin(); it != k.end(); ++it){
        cout << it->first + ":" + to_string(it->second) + ", " << endl;
        cout << endl;
    }*/

    return 0;
}
