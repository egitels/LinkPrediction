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
    //std::string GRAPH_FILE = "edgelists/as-ph/1994.txt";
    std::ifstream edgeList;
    edgeList.open(graph_file);

    std::string line;
    if (edgeList.is_open()){
        std::string throwaway;
        getline (edgeList, throwaway);
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
    pair<string, string> biggest = findLargestJaccard<string>(graph1);
    cout << "Biggest " << biggest.first << " " << biggest.second << endl;
    
    //cout << graph1.toString() << endl;
    //cout << graph2.toString() << endl;
    //cout << graph1.getSize() << endl;
    //cout << graph2.getSize() << endl; 
    
    //UndirectedUnweightedGraph<string> graph; 
    //graph.addEdge("A", "B"); 
    //graph.addEdge("A", "D");
    //graph.addEdge("B", "D");
    //graph.addEdge("C", "D");
    //graph.addEdge("C", "E");
    //graph.addEdge("C", "F");
    //graph.addEdge("B", "C");
    //graph.addEdge("B", "F");
    //graph.addEdge("D", "G");
    //
    //graph.addEdge("D", "H");
    //graph.addEdge("D", "J");
    //graph.addEdge("D", "Z");
    //graph.addEdge("H", "I");
    //graph.addEdge("J", "K");
    //graph.addEdge("J", "H");
    //graph.addEdge("Z", "Y");
    //
    //graph.addEdge("app", "G");
    //graph.addEdge("app", "J");
    //graph.addEdge("app", "oh");
    //graph.addEdge("app", "my");
    //cout << "\nCommon neighbors between C and A:" << endl;
    //vector<string> common = graph.commonNeighbors("C", "A");
    //for (string node : common){
    //    cout << node << " ";
    //}
    //cout << endl;
    //
    //cout << graph.preferentialAttachment("C", "A") << endl;

    //pair<string, string> biggest = findLargestJaccard<string>(graph);
    //cout << "Biggest " << biggest.first << " " << biggest.second << endl;

    
    return 0;
}
