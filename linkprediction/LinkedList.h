#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
using namespace std;
class LinkedList{
    public: 
        struct node{ //node struct  -> this is a vertex in the graph
            int weight;
            int data;
            struct node* next;
        };

        LinkedList();
        void add(int data, int weight);
        bool contains(int data);
        void remove();
        node* getHead() const;
        node* getCurrent() const;
        friend ostream &operator << (ostream &out, const LinkedList &n);
    private:
        node* head;
        node* current;
        node* newNode(int data, int weight);
};

#endif
