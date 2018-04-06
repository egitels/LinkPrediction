#include "LinkedList.h"
#include <stdlib.h>
#include <sstream>
#include <iostream>

LinkedList::LinkedList(){
    head = NULL;
    current = NULL;
}

void LinkedList::add(int data, int weight){
    node* nIn = newNode(data, weight);
    
    if (head == NULL){
        head = nIn;
        current = nIn;
    } else {
        current->next = nIn;
        current = nIn;
    }
}

bool LinkedList::contains(int data){
    node* current = getHead();
    while (current != NULL){
        if (current->data == data){
            return true;
        }
        current = current->next;
    }
    return false;
}

LinkedList::node* LinkedList::getHead() const{
    return head;
}

LinkedList::node* LinkedList::getCurrent() const{
    return current;
}


ostream & operator << (ostream &out, const LinkedList &n){
    LinkedList::node* current = n.getHead();
    while (current != NULL){
        out << "->" << current->data << "{" << current->weight << "} "; 
        current = current->next;
    }
    return out;
}

LinkedList::node* LinkedList::newNode(int data, int weight){
    node* newNode = (struct node*)malloc(sizeof(struct node*));
    newNode->data = data;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}



