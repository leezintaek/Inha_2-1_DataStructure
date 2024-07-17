#include <iostream>
#include <string>
using namespace std;

class Node{
friend class List;
private:
    Node* prev{nullptr};
    Node* next{nullptr};
    int element;
public:
    Node();
    Node(int element);
};

class Stack{
private:
    Node* head;
    Node* tail;
public:
    Stack();
};

Node::Node(){
    element = 0;
}

Node::Node(int element){
    this->element = element;
}

Stack::Stack(){
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}