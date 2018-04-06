#ifndef LinkedList_h
#define LinkedList_h

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
        node* getHead();
        node* getCurrent();

    private:
        node* head;
        node* current;
        node* newNode(int data, int weight);
};

#endif
