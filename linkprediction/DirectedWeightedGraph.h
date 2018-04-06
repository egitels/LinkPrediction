#include <vector>
#include <stdlib.h> //NULL
using namespace std;


class DirectedWeightedGraph {// graph is an adjlist representation. we want a vector of linkedlists.
public:
    
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
    
    node *current = NULL;
    int V;
    DirectedWeightedGraph(int V);
    void addEdge(int src, int dest, int destWeight);
    vector<node> adjVector;    
};

